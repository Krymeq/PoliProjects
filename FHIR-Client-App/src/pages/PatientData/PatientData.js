import React, { useState, useEffect } from 'react';
import { useParams, Link } from 'react-router-dom';
import { serverURL } from '../../config';
import { removeNumbersFromString,
         capitalize,
         maritalCodeToString } from '../../utils';
import './PatientData.scss';

const PatientData = () => {
    const { id } = useParams();
    const [patient, setPatient] = useState(undefined);

    useEffect(() => {
        fetch(`${serverURL}/Patient/${id}`)
        .then(res => res.json())
        .then(res => setPatient(res));
    }, [id])

    return (
    <div className="patient-data-root">
        <header>
            <span>
                {!patient ? "Loading..." 
                : `${removeNumbersFromString(`${patient.name[0].given[0]} ${patient.name[0].family}`)}`}
            </span>
        </header>
        <main>{ !patient ? "" :
            <div className="data-container">
                <div className="section">
                    <div className="header">
                        Patient Name
                    </div>
                    <div className="entries">
                    <div className="entry">
                        <span className="attribute">Name</span>
                        <span className="value">{removeNumbersFromString(patient.name[0].given[0])}</span>
                    </div>
                    <div className="entry">
                        <span className="attribute">Surname</span>
                        <span className="value">{removeNumbersFromString(patient.name[0].family)}</span>
                    </div>
                    {!!patient.name[1] ?
                        <div className="entry">
                            <span className="attribute">Maiden Name</span>
                            <span className="value">{removeNumbersFromString(patient.name[1].family)}</span>
                        </div> : ""}
                    </div>
                </div>
                <div className="section">
                    <div className="header">
                        Patient Info
                    </div>
                    <div className="entries">
                        <div className="entry">
                            <span className="attribute">Gender</span>
                            <span className="value">{capitalize(patient.gender)}</span>
                        </div>
                        <div className="entry">
                            <span className="attribute">Date of birth</span>
                            <span className="value">{patient.birthDate}</span>
                        </div>
                        <div className="entry">
                            <span className="attribute">Marital status</span>
                            <span className="value">{maritalCodeToString(patient.maritalStatus.text)}</span>
                        </div>
                    </div>
                </div>
                <div className="section">
                    <div className="header">
                        Address
                    </div>
                    <div className="entries">
                        <div className="entry">
                            <span className="attribute">Street</span>
                            <span className="value">{`${patient.address[0].line}`}</span>
                        </div>
                        <div className="entry">
                            <span className="attribute">City</span>
                            <span className="value">{`${patient.address[0].city}`}</span>
                        </div>
                        <div className="entry">
                            <span className="attribute">State</span>
                            <span className="value">{`${patient.address[0].state}`}</span>
                        </div>
                        <div className="entry">
                            <span className="attribute">Country</span>
                            <span className="value">{`${patient.address[0].country}`}</span>
                        </div>
                    </div>
                </div>
                <div className="section">
                    <div className="header">
                        Contact
                    </div>
                    <div className="entries">
                        {patient.telecom.map(entry => 
                        <div className="entry" key={entry.value}>
                            <span className="attribute">{capitalize(entry.system)}</span>
                            <span className="value">{entry.value}</span>
                        </div>)}
                    </div>
                </div>
            </div> }
            <div className="buttons">
                <Link to="/patients">
                    <span>Back</span>
                </Link>
                <Link to={`/medications/${id}`}>
                    <span>Medications</span>
                </Link>
                <Link to={`/observations/${id}`}>
                    <span>Observations</span>
                </Link>
            </div>
        </main>
    </div>)
}

export default PatientData;