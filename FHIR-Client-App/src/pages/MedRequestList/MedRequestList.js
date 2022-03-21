import React, { useState, useEffect } from 'react';
import {} from '@material-ui/pickers';
import { TextField } from "@material-ui/core";
import MedRequest from './MedRequest';
import { useParams, Link } from 'react-router-dom';
import { serverURL } from '../../config';
import { removeNumbersFromString } from "../../utils";
import "./MedRequestList.scss";

const MedRequestList = props => {
    const { id } = useParams();
    const [observations, setObservations] = useState(null);
    const [subject, setSubject] = useState(null);
    const [nextPage, setNextPage] = useState("");
    const [prevPage, setPrevPage] = useState("");
    const [url, setURL] = useState(`${serverURL}/MedicationRequest?subject=${id}`);
    const [firstDate, setFirstDate] = useState("");
    const [secondDate, setSecondDate] = useState("");

    const handleResponse = res => {
        const next = res.link.find(e => e.relation === "next");
        const prev = res.link.find(e => e.relation === "previous");
        setObservations(res.entry ? res.entry : []);
        setNextPage(!!next ? next.url : "");
        setPrevPage(!!prev ? prev.url : "");
    }

    const setURLBasedOnDates = (date1, date2) => {
        if(date1 != "" && date2 != ""){
            if(new Date(date1).getTime() < new Date(date2).getTime()){
                setURL(`${serverURL}/MedicationRequest?subject=${id}&date=>=${date1}&date=<=${date2}`);
            }
            else alert("Invalid date values!")
        }
        else if(date2 != ""){
            setURL(`${serverURL}/MedicationRequest?subject=${id}&date=<=${date2}`)
        }
        else if(date1 != ""){
            setURL(`${serverURL}/MedicationRequest?subject=${id}&date=>=${date1}`);
        }
        else setURL(`${serverURL}/MedicationRequest?subject=${id}`);
    }

    useEffect(() => {
        fetch(url)
        .then(res => res.json())
        .then(res => 
            {   
                console.log(url);
                console.log(res);
                handleResponse(res);
            });

        fetch(`${serverURL}/Patient/${id}`)
        .then(res => res.json())
        .then(res => setSubject(res));
    }, [id, url])

    const sortFunc = (a, b) => {
        const dateA = new Date(a.resource.authoredOn).getTime();
        const dateB = new Date(b.resource.authoredOn).getTime();

        if (dateA > dateB) return -1;
        if (dateA === dateB) return 0;
        if (dateA < dateB) return 1;
    }

    return <div className="observations-root">
        <header>
            <span>
                {!subject ? "Loading..." 
                : `${removeNumbersFromString(`${subject.name[0].given[0]} ${subject.name[0].family}`)} - medication requests`}
            </span>
        </header>
        <main>
        <div className="date-picker-container">
                <div className="date-picker">
                    <div className="padding">
                        <TextField
                            type="date"
                            label="From"
                            value={firstDate}
                            onChange={e => setFirstDate(e.target.value)}
                            InputLabelProps={{
                                shrink: true,
                            }}/>
                    </div>
                    <div className="padding">
                        <TextField
                            type="date"
                            label="To"
                            value={secondDate}
                            onChange={e => setSecondDate(e.target.value)}
                            InputLabelProps={{
                                shrink: true,
                            }}/>    
                    </div>
                    <div className="padding">    
                        <button onClick={() => setURLBasedOnDates(firstDate, secondDate)}>
                            Set date
                        </button>
                    </div>
                </div>
            </div>
            <div className="content-container">
                { !observations 
                ? <span>Loading...</span>
                : observations.length === 0 
                    ? <span>No medication requests available</span>
                    : observations.sort(sortFunc).map(observation => 
                    <MedRequest
                        key={observation.resource.id}
                        observation={observation}/>
                    )}
                <div className="links">
                    <Link to={`/patient/${id}`}>
                        <span>Patient Data</span>
                    </Link>
                    {prevPage !== "" ? <button onClick={() => setURL(prevPage)}>Previous</button> : ""}
                    {nextPage !== "" ? <button onClick={() => setURL(nextPage)}>Next</button> : ""}
                </div>
            </div>
        </main>
    </div>;
}

export default MedRequestList;