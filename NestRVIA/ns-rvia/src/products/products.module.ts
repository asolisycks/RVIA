import { Module } from '@nestjs/common';
import { ProductsService } from './products.service';
import { ProductsController } from './products.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Tbl_Product, Tbl_ProductImage } from './entities';

@Module({
  controllers: [ProductsController],
  providers: [ProductsService],
  imports: [
    // Aqui se van a importar los repositorios de cada entidad que queremos  utilizar en este modulo, es decir,TypeOrmModule.forFeature([Product])
    TypeOrmModule.forFeature([
      Tbl_Product, 
      Tbl_ProductImage
    ]) 
  ],
  exports: [
    ProductsService,
    TypeOrmModule,
  ]
})
export class ProductsModule {}
