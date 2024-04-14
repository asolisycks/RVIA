import { Injectable } from '@nestjs/common';
import { ProductsService } from './../products/products.service';
import { initialData } from './data/seed-data';


@Injectable()
export class SeedService 
{
  constructor(
    private readonly producService: ProductsService
  ){}

  async executeSeed()
  {
    await this.insertNewProducts();

    return 'SEED EXECUTE';
  }

  private async insertNewProducts()
  {
    await this.producService.deleteAllProducts();

    const products = initialData.products;

    const insertPromises = [];

    products.forEach(product => 
      {
        insertPromises.push(this.producService.create(product));
      });

    await Promise.all(insertPromises);
    
    return true;
  }
}
