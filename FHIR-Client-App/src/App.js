import React from 'react';
import { BrowserRouter as Router, Switch, Route, Redirect } from 'react-router-dom';
import './App.css';
import PatientList from './pages/PatientList/PatientList';
import PatientData from './pages/PatientData/PatientData';
import MedRequestList from './pages/MedRequestList/MedRequestList';
import ObservationList from './pages/ObservationList/ObservationList';

function App() {
  return (
    <div className="App">
      <Router>
        <Switch>
          <Route path="/patients">
            <PatientList/>
          </Route>
          <Route path="/patient/:id">
            <PatientData/>
          </Route>
          <Route path="/medications/:id">
            <MedRequestList/>
          </Route>
          <Route path="/observations/:id">
            <ObservationList/>
          </Route>
          <Route path="/">
            <Redirect to="/patients"/>
          </Route>
        </Switch>
      </Router>
    </div>
  );
}

export default App;
