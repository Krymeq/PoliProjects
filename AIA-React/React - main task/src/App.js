import React from 'react';
import './App.css';
import Content from './components/Content.js'

function App() {
  return (
    <div className="App">
      <header>
        <h1>
          Game Collector
        </h1>
      </header>
      <main>
        <Content/>
      </main>
    </div>
  );
}

export default App;
