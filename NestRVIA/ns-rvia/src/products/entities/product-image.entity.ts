import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import { Tbl_Product } from "./product.entity";

@Entity({ name: 'tbl_product_images' })
export class Tbl_ProductImage
{
    @PrimaryGeneratedColumn()
    id: number;
    
    @Column('text')
    url: string;

    @ManyToOne(
        type => Tbl_Product,
        product => product.images,
        {
            onDelete: 'CASCADE'
        }
    )
    product: Tbl_Product

}