import React from "react"

class PopupItem extends React.Component {
    render(){
        const item = this.props.item;
        return(
            <tr>
                <td>
                    <div className="remove-item-btn" onClick ={() => this.props.removeItem(item.id)}>
                        <img src="/assets/iksik.png" alt="usuń"></img>
                    </div>
                </td>
                <td>
                    {item.name}
                </td>
                <td style={{textAlign: "center"}}>
                    {item.quantity}
                </td>
                <td>
                    {item.price.toFixed(2)}
                </td>
                <td>
                    {(item.price * item.quantity).toFixed(2)}
                </td>
            </tr>
        )
    }
}

export default PopupItem;