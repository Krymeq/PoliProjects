import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ItemService } from './item.service';
import { ItemController } from './item.controller';
import { Item } from './Item'

@Module({
    imports: [TypeOrmModule.forFeature([Item])],
    exports: [TypeOrmModule],
    providers: [ItemService],
    controllers: [ItemController]
  })
export class ItemModule {}