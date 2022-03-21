import React from 'react'

class BasketItem extends React.Component {
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
            <button onClick={() => 
                    this.props.removeItem(this.props.item.id)}>
                    Usuń z koszyka
            </button>
        </div>
        )
    }
}

export default BasketItem;