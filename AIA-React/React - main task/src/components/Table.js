import React from 'react';
import TableRow from './TableRow';

class Table extends React.Component {
    render(){
        let tableRows = this.props.data.map(e => 
            <TableRow 
                element={e} 
                key={e.id} 
                active={e.active}
                changeObject={this.props.changeObject}
                removeElement={this.props.removeElement}
            />)
        
        return(
        <table>
            <tbody>
                <tr className = "header">
                    <th className="centered">Icon</th><th>Title</th><th>Description</th><th className="centered">Rating</th><th></th>
                </tr>
                    {tableRows}
            </tbody>
        </table>)
    }
}

export default Table;