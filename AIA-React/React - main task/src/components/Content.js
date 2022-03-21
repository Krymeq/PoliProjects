import React from 'react';
import initialData from '../data.json';
import Table from './Table';

class Content extends React.Component {
    constructor(props){
        super(props);
        initialData.forEach(e=>{e.active = false});
        this.state = {
            data: initialData,
            text: "",
            inversed: false,
            length: initialData.length
        };
        this.sortArray = this.sortArray.bind(this);
        this.filter = this.filter.bind(this);
        this.removeElement = this.removeElement.bind(this);
        this.changeObj = this.changeObj.bind(this);
    }

    // Funkcja sortująca elementy w tablicy danych.
    sortArray = (arr, inv) => {
        let modifier = inv ? -1 : 1;
        let sorted = arr.sort((a, b)=>{
            if(a.rating * modifier > b.rating * modifier) return 1;
            else if(a.rating === b.rating) return 0;
            else return -1;
        });
        return sorted;
    }

    newItem = () => {
        this.setState({data: 
            this.state.data.concat([
                {
                    icon: "",
                    title: "",
                    description:"",
                    rating: "",
                    id: this.state.data.length,
                    active: true
                }
            ])})
    }

    filter = (arr) => {
        let filtered = arr.filter
            (e => e.title
                    .toLowerCase()
                    .includes(this.state.text.toLowerCase()));
    
        return filtered;
    }

    removeElement = (id) => {
        let filtered = this.state.data
            .filter((e) => e.id !== id);
        this.setState({data: filtered});
    }

    changeObj = (id, newObject) => {
        this.setState({data: this.state.data.map(e=>{
            if(e.id === id){
                let newObj = Object.assign({}, e, newObject);
                return newObj;
            }
            else return e;
        })});
    }

    render() {
        let that = this;
        return (
        <div className="main-content">
            <div className="outer">
                <div>
                    <span>Search: </span>
                    <input
                        spellCheck="false"
                        value={that.state.text}
                        onChange={(e)=>{that.setState({text: e.target.value})}}
                    />
                </div>
                <div className="outer">
                    <span>Sort by rating: </span>
                    <div className="button-outer">
                        <div className={`button ${that.state.inversed ? "rotated" : ""}`}
                             onClick={()=>{that.setState({inversed: !that.state.inversed})}}>
                            <img src="/assets/arrow.png" alt="Arrow"/>
                        </div>
                        <div className="button"
                             onClick=
                             {()=>
                                {that.setState(
                                {data: that.sortArray(that.state.data, !that.state.inversed)
                        })}}>
                            <span>Sort</span>
                        </div>
                    </div>
                </div>
            </div>
            <Table data={this.filter(this.state.data)}
                   removeElement={this.removeElement}
                   changeObject={this.changeObj}/>
            
            <div className="outer">
                <div className="button-outer">
                    <div className="button" onClick={()=>{that.newItem()}}>New item</div>
                </div>
            </div>
            <footer>
                TIP: You can pass as icon either absolute, relative (according to this app's public/ folder) or even web URL links.
            </footer>
        </div>
        );
    }
}

export default Content;