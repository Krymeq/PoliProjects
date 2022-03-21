import React from "react"
import './Game.css'

class Game extends React.Component {
    constructor(props){
        super(props);
        this.getQuestionByID = this.getQuestionByID.bind(this);
        this.getNextQuestionFromChoice = this.getNextQuestionFromChoice.bind(this);
        this.calculateDivWidth = this.calculateDivWidth.bind(this);
        this.state = {
            currentQuestion : this.getQuestionByID(
                this.props.story.storyline,
                this.props.story.startQuestID)
        }
    }

    // Function returns question with given ID.
    getQuestionByID(questions, id) {
        console.log(id);
        let res = questions.filter(e => e.id === id)[0];
        return res;
    }

    // function responsible for more clever word - wrapping.
    calculateDivWidth(text){
        let res = Math.round(Math.sqrt(text.length * 17)) * 6;
        let width = (res < 1200) ? res : 1200;
        return ({maxWidth: `${width}px`});
    }

    getNextQuestionFromChoice(choice){
        let chance = 1.0;
        if(choice.hasOwnProperty("chance")){
            chance = choice.chance;
        }

        if(!choice.hasOwnProperty("failure")){
            return choice.success;
        }

        let result = Math.random();
        let res = (result <= chance) ? choice.success : choice.failure;
        return res;
    }

    render(){
        let that = this;
        let question = this.state.currentQuestion;
        let choices = question.choices.map(e => 
            <button 
                key = {e.text}
                onClick = {() => 
                    that.setState({currentQuestion :
                        that.getQuestionByID(
                            that.props.story.storyline,
                            that.getNextQuestionFromChoice(e))
                        })}
                >{e.text}</button>);
        return (
            <div className = "game">
                <span style={this.calculateDivWidth(question.text)}>
                    {question.text}
                </span>
                <div className = "choices">
                    {choices}        
                </div>
            </div>
        )
    }
}

export default Game;