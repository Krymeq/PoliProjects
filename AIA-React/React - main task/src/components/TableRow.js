import React from 'react'

class TableRow extends React.Component {    
    constructor(props){
        super(props);
        let e = this.props.element;
        this.state = {
            title: e.title,
            description: e.description,
            rating: e.rating,
            icon: e.icon
        }
        
        this.validateData.bind(this);
    }

    validateData = (data, range) => {
        if(!isNaN(data) && data !== ""){
            if(range[0] <= data && data <= range[1]){
                return true;
            }
        }
        return false;
    }
    
    render() {
        let e = this.props.element;
        let editableRow = (
            <tr className = "row editable-row">
                <td className="centered">
                    <input value={this.state.icon}
                           onChange={e => this.setState({icon: e.target.value})}/>
                </td>
                <td>
                    <input value={this.state.title} 
                           onChange={(e)=>this.setState({title: e.target.value})}/>
                </td>
                <td>
                    <div className="text-area">
                        <textarea value={this.state.description}
                            onChange={e => this.setState({description: e.target.value})}/>
                    </div>
                </td>
                <td className="centered">
                    <input className="rating" value={this.state.rating}
                           onChange={e => this.setState({rating: e.target.value})}/>
                </td>
                <td>
                    <button onClick={
                        ()=>{
                            if(this.validateData(this.state.rating, [0, 10]) === true){
                                this.props.changeObject(e.id, Object.assign({}, this.state, {active: !e.active}))}
                            else {
                                alert(`Invalid rating: ${this.state.rating}. Rating should be between 0 and 10 (inclusive)`)
                            }
                        }
                    }>Save</button>
                </td>
            </tr>
        )

        let normalRow = (
            <tr className = "row normal-row" onClick={()=>this.props.changeObject(e.id, {active: !e.active})}>
                <td className="centered">
                    <img src={e.icon} alt="404 content not found"/>
                </td>
                <td>
                    {e.title}
                </td>
                <td>
                    {e.description}
                </td>
                <td className="centered">
                    {e.rating}
                </td>
                <td>
                    <button onClick={(event)=>{
                        event.stopPropagation();
                        this.props.removeElement(e.id)}}>Delete</button>
                </td>
            </tr>
        )           
        return !e.active ? normalRow : editableRow;
    }
}

export default TableRow;