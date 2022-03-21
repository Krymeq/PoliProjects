import React from 'react';
import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css'
import Navbar from './Navbar.js'
import DataContainer from './DataContainer.js'

function App() {
  return (
    <div className="App">
      <Navbar/>
      <DataContainer/>
    </div>
  );
}

export default App;
