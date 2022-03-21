import React, { useState } from 'react'
import { dateToString, removeNumbersFromString } from "../../utils";
import { Collapse } from '@material-ui/core';

const DetailsItem = props => {
    return <div className="details" {...props}>
                <div className="detail-item">
                    <div className="title">
                        Requester
                    </div>
                    {removeNumbersFromString(props.requester)}
                </div>
                <div className="detail-item">
                    <div className="title">
                        Requested on
                    </div>
                    {dateToString(new Date(props.requestedon))}
                </div>
                {!!props.dosageInstruction ?
                <div className="detail-item">
                    <div className="title">
                        Dosage instruction
                    </div>
                    {`${props.dosageInstruction[0].sequence} pill(s) daily`}
                </div>
                : ""}
            </div>
}

const MedRequest = props => {
    const resource = props.observation.resource;
    const [details, showDetails] = useState(false);

    return (
    <div className="observation" onClick={() => showDetails(!details)}>
        <div className="date">
            { dateToString(new Date(resource.authoredOn)) }
        </div>
        <div className="item">
            { resource.medicationCodeableConcept.text }
        </div>
        <Collapse in={details}>
            <DetailsItem 
                requester={resource.requester.display}
                requestedon={resource.authoredOn}
                dosageInstruction={resource.dosageInstruction}/>
        </Collapse>
    </div>)
}

export default MedRequest;