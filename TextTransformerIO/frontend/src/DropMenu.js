import React from 'react';
import Dropdown from 'react-bootstrap/Dropdown'

class DropdownMenu extends React.Component {
    
    constructor(props){
        super(props);

        console.log(this.props.identity);
        
        this.setSelection = this.setSelection.bind(this);
    }

    setSelection(e){
        this.props.changeState(this.props.identity, e);
    }

    render(){
        let menuOptions = this.props.values.map((e) => 
            <Dropdown.Item
            onSelect={() => this.setSelection(e)}
            key={e}>
                {e}
            </Dropdown.Item>
        );
        return (
            <Dropdown className = 'btnstyle'>
                <Dropdown.Toggle variant="success" id="dropdown">
                    {this.props.selected}
                </Dropdown.Toggle>

                <Dropdown.Menu>
                    {menuOptions}
                </Dropdown.Menu>
            </Dropdown>
        )
    }
}

export default DropdownMenu