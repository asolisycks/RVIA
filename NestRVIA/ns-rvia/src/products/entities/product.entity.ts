import { BeforeInsert, BeforeUpdate, Column, Entity, OneToMany, PrimaryGeneratedColumn } from "typeorm";
import { Tbl_ProductImage } from "./product-image.entity";

@Entity({ name: 'tbl_products' })
export class Tbl_Product {
    
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @Column( 'text', {
        unique: true
    })
    title: string;

    @Column(  'double precision', { 
        default: 0.0
    })
    price: number;

    @Column('text',{
        nullable: true
    })
    description: string;

    @Column( 'text', {
        unique: true
    })
    slug: string;

    @Column( 'int', {
        default: 0
    })
    stock: number;

    @Column( 'text', {
        array: true
    })
    sizes: string[];

    @Column('text')
    gender: string;

    //tags
    @Column( 'text', {
        array: true,
        default: []
    })
    tags: string[];

    //images
    @OneToMany(
        () => Tbl_ProductImage,
        (productImage) => productImage.product,
        { cascade: true, eager: true }
    )
    images?: Tbl_ProductImage[];

    @BeforeInsert()
    checkSlugInsert()
    {
        if (!this.slug) 
        {
            this.slug = this.title;
        }

        this.slug = this.slug
            .toLowerCase()
            .replaceAll(' ', '_')
            .replaceAll("'", '');
    }

    @BeforeUpdate()
    checkSlugUpdate()
    {
        this.slug = this.slug
            .toLowerCase()
            .replaceAll(' ', '_')
            .replaceAll("'", '');
    }
}
