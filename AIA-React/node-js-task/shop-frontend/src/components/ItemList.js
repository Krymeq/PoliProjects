import React from 'react'
import Item from './Item'

class ItemList extends React.Component {
    componentDidMount() {
        this.props.toggleBasketButton(true);
    }

    render(){
        console.log(this.props.items);
        const items = this.props.items
            .map(e =>
                <Item 
                    item={e} 
                    key={e.id}
                    addItem={this.props.addItem}
                />);
        return (
        <div className="item-list">
            <div className="item-list-row">
                <div className="table-header">
                    <span>Nazwa</span>
                    <span>Cena</span>
                    <span>Ilość</span>
                </div>
            </div>
            {items}
        </div>);
    }
}

export default ItemList;