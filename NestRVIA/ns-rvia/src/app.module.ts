import { Module } from '@nestjs/common';
import { ConfigModule } from '@nestjs/config';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ProductsModule } from './products/products.module';
import { CommonModule } from './common/common.module';
import { SeedModule } from './seed/seed.module';
import { FilesModule } from './files/files.module';
import { ServeStaticModule } from '@nestjs/serve-static';
import { join } from 'path';
import { AuthModule } from './auth/auth.module';


@Module({
  imports: [
    ConfigModule.forRoot(),
    TypeOrmModule.forRoot({
      type: 'postgres',
      host: process.env.DBH,
      port: parseInt(process.env.DBP),
      username: process.env.DBU,
      password: process.env.DBPW,
      database: process.env.DBN,
      autoLoadEntities: true,
      synchronize: true, //TODO: set to false in production
    }),
    ServeStaticModule.forRoot(
      { 
        rootPath: join( __dirname, '..', 'public')
      }
    ),
    ProductsModule,
    CommonModule,
    SeedModule,
    FilesModule,
    AuthModule,
  ]
})
export class AppModule {}
