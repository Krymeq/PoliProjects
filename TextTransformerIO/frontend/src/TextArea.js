import React from 'react'

class TextArea extends React.Component {
    constructor(props){
        super(props);
        
        this.state = {
            text: 'Enter text here'
        }

        this.onChange = this.onChange.bind(this);
    }

    onChange(event){
        this.props.changeState(this.props.name, event.target.value);
    }

    render() {
        const text = this.props.value;
        return (
            <div className = 'textarea-container'>
                <textarea 
                    spellcheck = 'false'
                    className = 'text-area' 
                    value = {text}
                    onChange = {this.onChange}/>
            </div>
        )
    }
}

export default TextArea;