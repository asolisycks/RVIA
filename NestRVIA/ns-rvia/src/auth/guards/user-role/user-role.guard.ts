import { BadRequestException, CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Reflector } from '@nestjs/core';
import { Observable } from 'rxjs';
import { User } from 'src/auth/entities/user.entity';

@Injectable()
export class UserRoleGuard implements CanActivate 
{
  constructor(
    private readonly reflector: Reflector,
  ){}
  
  canActivate(
    context: ExecutionContext,
  ): boolean | Promise<boolean> | Observable<boolean> 
  {

    //console.log('Inside the user role guard');
    const validRoles : string[] = this.reflector.get( 'roles', context.getHandler() );

    //console.log({validRoles});

    const req = context.switchToHttp().getRequest();
    const user = req.user as User;
    
    console.log({userRole: user.roles});

    if( !user )
    {
      throw new BadRequestException("User is not logged in");
    }

    for( const role of  user.roles )
    {
      if( validRoles.includes( role ) )
      {
        return true;
      }
    }

    throw new BadRequestException(
      `The user "${user.fullName}" need a valid role [${validRoles}]`
    );
  }
}
