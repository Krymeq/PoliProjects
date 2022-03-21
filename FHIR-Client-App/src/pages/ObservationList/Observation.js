import React, { useState } from 'react';
import { dateToString } from '../../utils'
import { Collapse } from '@material-ui/core';

const Details = props => {
    console.log(props.value);
    return <div className="details">
        {props.value ?
        <div className="parent">
            <div className="title">
                value
            </div>
            <div className="detail-item">
                {`${props.value.value} ${props.value.unit !== `{score}` ? props.value.unit : ""}`}
            </div>
        </div>
        : ""}
        {props.categories.map(category => 
            <div className="parent">
                <div className="title">
                    Category
                </div>
                <div className="detail-item">
                    {category.coding[0].display}
                </div>
            </div>)}
        <div className="parent">
            <div className="title">
                Issued on
            </div>
            <div className="detail-item">
                {dateToString(new Date(props.issuedOn))}
            </div>
        </div>
    </div>
}


const Observation = props => {
    const item = props.observation.resource;
    const [details, showDetails] = useState(false);
    return(
    <div className="observation" onClick={() => showDetails(!details)}>
        <div className="date">
            {dateToString(new Date(item.issued))}
        </div>
        <div className="item">
            {item.code.text}
        </div>
        <Collapse in={details}>
            <Details 
                value={item.valueQuantity}
                categories={item.category}
                issuedOn={item.issued}/>
        </Collapse>
    </div>) 
}

export default Observation;