import { BadRequestException, Injectable, InternalServerErrorException, Logger, UnauthorizedException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { JwtService } from '@nestjs/jwt';

import { Repository } from 'typeorm';

import * as bcrypt from 'bcrypt';

import { User } from './entities/user.entity';
import { CreateUserDto, LoginUserDto } from './dto';
import { JwtPayload } from './interfaces/jwt-payload.interfaces';

@Injectable()
export class AuthService 
{
  private readonly logger = new Logger(AuthService.name);

  constructor(
    @InjectRepository(User)
    private readonly userRepository: Repository<User>,
    private readonly jwtService: JwtService
  ){}

  async create(createUserDto: CreateUserDto) 
  {
    try 
    {
      const { password, ...userData } = createUserDto;

      const user = this.userRepository.create({
        ...userData,
        password: bcrypt.hashSync(password, 10)
      });

      await this.userRepository.save(user);

      delete user.password;

      return {
        ...user,
        token: this.getJwtToken({ id: user.id })
      };
    } 
    catch (error) 
    {
      this.logger.error(error.message, error.stack);
      this.handelDBErrors( error );
    }
  }

  private getJwtToken( payload: JwtPayload )
  {
    const token = this.jwtService.sign( payload );
    return token;
  }

  async login( loginUserDto: LoginUserDto)
  {
      const { password, email } = loginUserDto;
      
      const user = await this.userRepository.findOne({
        where: { email },
        select: { email: true, password: true, id: true }
      });

      if (!user) 
      {
        throw new UnauthorizedException('Credentials are not valid (email)');
      }

      if (!bcrypt.compareSync(password, user.password)) 
      {
        throw new UnauthorizedException('Credentials are not valid (password)');
      }

      return {
        ...user,
        token: this.getJwtToken({ id: user.id })
      };
  }

  private handelDBErrors( error: any ) : never
  {
    if (error.code === '23505')
    {
      throw new BadRequestException(error.detail);
    }
    
    throw new InternalServerErrorException('Please check server logs');
  }
}
