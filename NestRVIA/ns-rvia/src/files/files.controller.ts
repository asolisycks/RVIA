import { Controller, Get, Post, Body, Patch, Param, Delete, UseInterceptors, UploadedFile, BadRequestException, Res } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { FileInterceptor } from '@nestjs/platform-express';

import { Response } from "express";
import { FilesService } from './files.service';
import { diskStorage } from 'multer';

import { fileFilter, fileNamer } from './helpers';

@Controller('files')
export class FilesController 
{
  constructor(
    private readonly filesService: FilesService,
    private readonly configService: ConfigService
    ) {}

  @Get('product/:imageName')
  findProductImage(
    @Res() res : Response,
    @Param('imageName') imageName : string
  )
  {
    const path = this.filesService.getStaticProductImage(imageName);
    
    /*res.status(403).json(
    {
      ok: false,
      path: path
    });*/

    res.sendFile(path);

    //return path;
  }


  @Post('product')
  @UseInterceptors( FileInterceptor('file',
  {
    fileFilter: fileFilter,
    limits: { fileSize: 1000000 },
    storage: diskStorage({
      destination: './static/products',
      filename: fileNamer
    })
  }) )
  uploadProductImage( 
    @UploadedFile() file: Express.Multer.File, 
    )
  {

    if (!file) 
    {
      throw new BadRequestException('Please provide a valid file');      
    }

    //const secureUrl = `${file.filename}`;
    const secureUrl = `${this.configService.get('HOST_API')}/files/product/${file.filename}`;

    return  {
      //originalName : file.originalname,
      secureUrl
    };
  }
}
