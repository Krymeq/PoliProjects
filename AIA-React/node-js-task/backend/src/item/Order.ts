import { Item } from "./Item";

export class Order {
    constructor(items: Item[]){
        this.items = items;
    }
    items : Item[];
}