import { Injectable } from "@nestjs/common";
import { Item } from "./Item";
import { Connection } from "typeorm";
import { Order } from "./Order";

@Injectable()
export class ItemService {
    
    constructor(private connection: Connection){}

    async getAllItems(): Promise<Item[]> {
        const res = await this.connection
            .createQueryBuilder()
            .select("items")
            .from(Item, "items")
            .getMany();
        
        return res;
    }

    async processOrder(order: Order): Promise<boolean>{
        let isValidOrder : boolean;
        const queryRunner = this.connection.createQueryRunner();
        const queryBuilder = this.connection.createQueryBuilder();
        await queryRunner.connect();
        await queryRunner.startTransaction("SERIALIZABLE");
        try {
            // query the database to get current state of warehouse
            const warehouse = await queryBuilder
                .select("items")
                .from(Item, "items")
                .getMany();
            isValidOrder = this.validateOrder(order, warehouse);
            if(isValidOrder)
            {
                for(let item of order.items){
                    await queryBuilder
                        .update(Item)
                        .set({quantity : () => `quantity - ${item.quantity}`})
                        .where("id = :id", {id : item.id})
                        .execute();
                    await queryRunner.commitTransaction();
                }
            }
            else 
                await queryRunner.rollbackTransaction();
        }
        catch(err){
            await queryRunner.rollbackTransaction();
        }
        finally {
            queryRunner.release();
            return isValidOrder;
        }
    }

    validateOrder(order: Order, warehouse: Item[]): boolean{
        for(let item of order.items){
            let itemState = warehouse.filter(e => e.id === item.id)[0];
            if(item.quantity > itemState.quantity)
                return false;
        }
        return true;
    }

    sampleFunc(param: number){
        console.log(param);
        if(param == 0) return false;
        else return true;
    }
}
