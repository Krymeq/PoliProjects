import React from 'react'
import DropdownMenu from './DropMenu.js'
import TextArea from './TextArea.js'
import Button from  'react-bootstrap/Button'

class Transformation {
    constructor(value, classID, transformID){
        this.value = value;
        this.classID = classID;
        this.transformID = transformID;
    }
}

const values = [
    'To upper case',
    'To lower case',
    'Inverse',
    'Capitalize',
    'Remove repetitions',
    'Words to shortcuts',
    'Shortcuts to words',
    'Symbols to LaTeX',
    'Numbers to words',
    'Caesar cipher',
    'Permutate'
]

const transforms = [
    new Transformation(values[0], 3, 0),
    new Transformation(values[1], 3, 1),
    new Transformation(values[2], 3, 2),
    new Transformation(values[3], 3, 3),
    new Transformation(values[4], 3, 4),
    new Transformation(values[5], 2, 0),
    new Transformation(values[6], 2, 1),
    new Transformation(values[7], 2, 2),
    new Transformation(values[8], 1, 1),
    new Transformation(values[9], 4, 0),
    new Transformation(values[10], 4, 1)
]

function getTransform(name)
{
    for (let i of transforms){
        if(i.value === name)
        {
            return i;
        }
    }
    return null;
}

class DataContainer extends React.Component
{
    constructor(props){
        super(props);

        this.state = {
            text: 'Enter sample text here.',
            variant: values[0],
            output: 'Result will appear here'
        }

        this.changeState = this.changeState.bind(this);
        this.onClick = this.onClick.bind(this);
    }

    changeState(name, value)
    {
        this.setState({
            [name]: value
        });
        
    }

    onClick()
    {
        let that = this;
        const transformation = getTransform(this.state.variant);
        const payload = {
            text: this.state.text,
            classID: transformation.classID,
            functionID: transformation.transformID
        }

        fetch("http://localhost:8080", 
        {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(payload)
        })
        .then(resp => resp.json())
        .then(ans => that.setState({output: ans.text}))
        .catch(() => that.setState({output: "An error occured"}));

    }

    render(){
        return (
            <div className = 'data-container'>
                <div className = 'button-container'>
                    <DropdownMenu
                        values={values} 
                        identity='variant' 
                        changeState = {this.changeState} 
                        selected={this.state.variant}
                    />
                    <Button className ="btnstyle" onClick = {this.onClick}>Send</Button>
                </div>
                <TextArea 
                    name='text' 
                    changeState = {this.changeState} 
                    value={this.state.text}
                />
                <TextArea
                    name='output'
                    changeState = {this.changeState}
                    value = {this.state.output}
                />
            </div>
        )
    }
}

export default DataContainer