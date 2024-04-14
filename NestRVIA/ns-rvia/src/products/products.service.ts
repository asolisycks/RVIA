import { BadRequestException, Injectable, InternalServerErrorException, Logger, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { DataSource, Repository } from 'typeorm';

import {validate as isUUID} from 'uuid';

import { CreateProductDto } from './dto/create-product.dto';
import { UpdateProductDto } from './dto/update-product.dto';
import { PaginationDto } from '../common/dtos/pagination.dto';
import { Tbl_Product, Tbl_ProductImage } from './entities';

@Injectable()
export class ProductsService 
{
  private readonly logger = new Logger(ProductsService.name);

  constructor(
    @InjectRepository(Tbl_Product)
    private readonly productRepository: Repository<Tbl_Product>,

    @InjectRepository(Tbl_ProductImage)
    private readonly productImageRepository: Repository<Tbl_ProductImage>,

    private readonly dataSource: DataSource,
  ) { }


  async create(createProductDto: CreateProductDto) 
  {  
    try 
    {

      const {images = [], ...productDetails} =  createProductDto;

      const product = this.productRepository.create({
        ...productDetails,
        images: images.map( image => this.productImageRepository.create({url: image}))
      });

      await this.productRepository.save(product);
      
      //return product;
      return { ...product, images: images };
    } 
    catch (error) 
    {
      this.handleDBExceptions(error);
    }
  }

  async findAll( paginationDto: PaginationDto )
  {
    //Destructurar paginationDto
    const { limit = 10, offset = 0} = paginationDto;
    
    const products = await this.productRepository.find({
      take: limit,
      skip: offset,
      relations: {
        images: true
      }
    });

    return products.map( product => ({
      ...product,
      images: product.images.map( img => img.url)
    }));
  }
    
  async findOne(term: string) 
  {
    let product : Tbl_Product;
    
    if (isUUID(term)) 
    {
      product = await this.productRepository.findOneBy({id: term});
    }
    else
    {
      //product = await this.productRepository.findOneBy({slug: term});

      const queryBuilder = this.productRepository.createQueryBuilder();
      product = await queryBuilder.where( 'UPPER(title) =: title OR slug =: slug',
        {
          title: term.toUpperCase(),
          slug: term.toLowerCase()
        }
        )
        .leftJoinAndSelect('product.images', 'images')
        .getOne();
    }

    //const product = await this.productRepository.findOneBy({id});

    if (!product) 
    {
      throw new NotFoundException(`El producto con id "${term}" no fue encontrado`);
    }

    return product;
  }

  async findOnePlain( term: string)
  {
    const { images = [], ...rest } = await this.findOne(term);
    
    return{
      ...rest,
      images: images.map( image => image.url),
    }
  }

  async update(id: string, updateProductDto: UpdateProductDto) 
  {
      const { images, ...toUpdate } = updateProductDto;

      const product = await this.productRepository.preload({ id, ...toUpdate });
      
      if (!product) 
      {
        throw new NotFoundException(`El producto con id "${id}" no fue encontrado`);
      }

      const queryRunner = this.dataSource.createQueryRunner();
      await queryRunner.connect();
      await queryRunner.startTransaction();

      try 
      {
        if (images) 
        {
          await await queryRunner.manager.delete(Tbl_ProductImage, {product: {id}});
          
          product.images = images.map( 
            image => this.productImageRepository.create({url: image})
          );
        }
        /*else
        {
          product.images = await this.productImageRepository.findBy( {product : {id}});
        }*/

        await queryRunner.manager.save(product);

        await queryRunner.commitTransaction();
        await queryRunner.release();

        //await this.productRepository.save(product);
        //return product;
        return this.findOnePlain(id);

      } 
      catch (error) 
      {
        this.handleDBExceptions(error);
      }
  }

  async remove(id: string)
  {
    const product = await this.findOne(id);

    await this.productRepository.remove(product);
    
    return product;
  }

  private handleDBExceptions( error: any)
  {
    if (error.code === '23505') 
    {
      throw new BadRequestException(error.detail);  
    }

    this.logger.error(error);
    throw new InternalServerErrorException('Unexpected error, check server logs!');
  }

  async deleteAllProducts()
  {
    const query = this.productRepository.createQueryBuilder('product');

    try
    { 
      return await query
      .delete()
      .where({})
      .execute();
    }
    catch (e) 
    {
      this.handleDBExceptions(e);
    }
  }
}
