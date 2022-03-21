import React from 'react';
import { Link } from 'react-router-dom';
import BasketItem from './BasketItem'

class Basket extends React.Component {
    constructor(props){
        super(props);
        this.dropBasket = this.dropBasket.bind(this);
        this.resolveOrder = this.resolveOrder.bind(this);
    }

    componentDidMount() {
        this.props.toggleBasketButton(false);
    }

    dropBasket(){
        for(const item of this.props.items){
                this.props.removeItem(item.id);
        }
    }

    resolveOrder(){
        if(this.props.items.length > 0){
            fetch("http://localhost:8080/shop/order", {
                method: "POST",
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({items: this.props.items})
            })
            .then(resp => resp.json())
            .then((resp) => {
                this.dropBasket();
                this.props.getItems();
                alert(resp.status);
            })
            .catch(err => console.error(err));
        }
        else 
            alert("Koszyk jest pusty");
    }

    handleClick(e, func){
        const isSure = window.confirm("Jesteś pewien?");
        if(!isSure)
            e.preventDefault();
        else 
            func();
    }

    render(){
    let items = this.props.items.map(e =>
        <BasketItem 
            item={e} 
            key={e.id}
            removeItem={this.props.removeItem}/>)
    
        return (
        <div>
            <span style={{
                display: 'block',
                textAlign: "left",
                fontWeight: "bold",
                padding: "10px"
            }}>Twój koszyk:</span>
            {
                items.length !== 0 ? 
                <div className="item-list">
                    <div className="item-list-row">
                        <div className="table-header">
                            <span>Nazwa</span>
                            <span>Cena</span>
                            <span>Ilość</span>
                        </div>
                    </div>
                    {items}
                </div>  
                : <span>Brak przedmiotów w koszyku.</span>
            }
            <div className="link-button-container">
                <Link to="/">
                    <div className="link-button">
                        Powrót     
                    </div>    
                </Link>
                <Link to="/">
                    <div className="link-button" onClick={(e) => this.handleClick(e, this.dropBasket)}>
                        Anuluj zakupy
                    </div>    
                </Link>
                <Link to="/" onClick = {(e) => this.handleClick(e, this.resolveOrder)}>
                    <div className="link-button">
                        Zakup
                    </div>    
                </Link>
            </div>
        </div>
        )
    }
}
export default Basket;