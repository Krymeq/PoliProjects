import React from 'react';
import './App.css';
import './style.css';
import ItemList from './components/ItemList';
import Popup from './components/Popup';
import Basket from './components/Basket';
import { Animated } from "react-animated-css";
import { Switch, Route } from 'react-router-dom';


class App extends React.Component {
  constructor(props){
    super(props);
    this.removeItemByID = this.removeItemByID.bind(this);
    this.addItemToBasket = this.addItemToBasket.bind(this);
    this.toggleBasketButton = this.toggleBasketButton.bind(this);
    this.getItems = this.getItems.bind(this);
    this.state = {
        items : [],
        basket: [],
        showBasketPopup: false,
        showBasketButton: true
    }
  }

  getItems(){
    fetch("http://localhost:8080/shop/list")
          .then(resp => resp.json())
          .then(e => this.setState({items: e}));
  }

  removeItemByID(id){
    this.setState({
      basket: this.state.basket.filter(e => e.id !== id)
    })
  }

  toggleBasketButton(val){
    this.setState({
      showBasketButton: val
    })
  }

  componentDidMount(){
    this.getItems();
  }

  // Function adding item to basket
  addItemToBasket(item){
    let basket = this.state.basket;
    let warehouse = this.state.items;
    let basketIndex = basket.findIndex((e) => e.id === item.id);
    let warehouseIndex = warehouse.findIndex((e) => e.id === item.id);
    
    // if item is present in basket
    if(basketIndex !== -1){
      if(parseInt(item.quantity) + basket[basketIndex].quantity <= warehouse[warehouseIndex].quantity)
        basket[basketIndex].quantity += item.quantity;
      else
        alert(`Zbyt mało przedmiotów typu ${item.name} w magazynie`);
    }

    // if there is no such item in the basket
    else {
      if(item.quantity <= warehouse[warehouseIndex].quantity){
        basket.push(item);
      }
      else
        alert(`Zbyt mało przedmiotów typu ${item.name} w magazynie`);
    }
    this.setState({basket: basket});
  }

  render(){
    return (
      <div className="App">
        <header>
          <span>
            Alledrogo
          </span>
          {this.state.showBasketButton ? 
            <div className={this.state.showBasketButton ? "popup-container" : "disabled"}>
              <div className="basket-button"
                  onClick={()=>this.setState({showBasketPopup: !this.state.showBasketPopup})}>
                <img src="/assets/basket.png" alt="404"/>
              </div>
                <Animated 
                    animationIn="fadeIn" 
                    animationOut="fadeOut" 
                    animationInDuration={200} 
                    animationOutDuration={200} isVisible={this.state.showBasketPopup}>
                  <Popup 
                    items={this.state.basket} 
                    removeItem={this.removeItemByID}/>
                </Animated>
            </div>
          : ""}
        </header>
        <main>
          <div className="main">
            <Switch>
              <Route path="/checkout">
                <Basket
                  items={this.state.basket}
                  getItems={this.getItems}
                  removeItem={this.removeItemByID}
                  toggleBasketButton={this.toggleBasketButton}
                  />
              </Route>
              <Route path="/">
                <ItemList
                  items={this.state.items}
                  addItem={this.addItemToBasket}
                  toggleBasketButton={this.toggleBasketButton}
                /> 
              </Route>
            </Switch>
          </div>
        </main>
      </div>
    );
  }
}

export default App;
