import React from "react"

class Item extends React.Component {
    constructor(props){
        super(props);
        this.promptForAmount = this.promptForAmount.bind(this);
    }

    promptForAmount(){
        const amount = prompt("Podaj ilość");
        console.log(amount);
        if(amount > 0){
            let item = Object.assign({}, this.props.item, {quantity: parseInt(amount)});
            this.props.addItem(item);
        }
        else if(amount !== null)
            alert("Podano niewłaściwą ilość")
    }
    
    render(){
        return (
        <div className="item-list-row">
            <div className = "item">
                <span>
                    {this.props.item.name}
                </span>
                <span>
                    {this.props.item.price.toFixed(2)}
                </span>
                <span style={{textAlign: "center"}}>
                    {this.props.item.quantity}
                </span>
            </div>
            <button onClick={() => this.promptForAmount()}>Dodaj do koszyka</button>
        </div>);
    }
}

export default Item;