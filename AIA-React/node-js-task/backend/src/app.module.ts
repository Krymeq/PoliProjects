import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm'
import { ItemModule } from './item/item.module';
import { Item } from './item/Item';

@Module({
  imports: [TypeOrmModule.forRoot(
    {           
      "type": "mysql",              // Database type
      "host": "localhost",          // URL and port of DB connection
      "port": 3306,
      "username": "foo",            // Username and password of the database
      "password": "bar1231,",   
      "database": "Shop",           // Name of the database app will connect to
      "entities": [Item],           
      "synchronize": false,
      "logging": true
    } 
  ), ItemModule],
})
export class AppModule {}
