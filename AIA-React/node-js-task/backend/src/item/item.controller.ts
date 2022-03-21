import { Controller, Get, Post, Req, Res } from "@nestjs/common";
import { Response } from "express"
import { Redirect } from "@nestjsplus/redirect"
import { Item } from "./Item";
import { ItemService } from "./item.service";
import { Request } from "express"

@Controller("shop") 
export class ItemController
{
    constructor(private itemService: ItemService){}

    @Get("list")
    getEachItem(): Promise<Item[]>{
        return this.itemService.getAllItems();
    }

    @Get("confirm")
    getConfirmation(): Object{
        console.log("Confirmed")
        return {status: "Zamówienie pomyślne"};
    }

    @Get("reject")
    getRejection(): Object {
        console.log("Rejected")
        return {status: "Zamówienie odrzucono"}
    }

    @Post("order")
    async processOrder(@Req() req: Request,
                       @Res() res: Response) 
    {
        console.log(req.body);
        const status = await this.itemService.processOrder(req.body);
        if(status)
            res.redirect("confirm");
        else 
            res.redirect("reject");
    }
}