import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';


@Entity("items")
export class Item {
    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    name: string;

    @Column()
    quantity: number;

    @Column()
    price: number;
}