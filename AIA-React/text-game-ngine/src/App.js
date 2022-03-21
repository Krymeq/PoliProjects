import React from 'react';
import './App.css';
import Game from './components/Game.js';
import story from './storyfile.json';

function App() {
  return (
    <div className="App">
      <header>{story.title}</header>
      <main>
        <Game story={story.quests}/>
      </main>
    </div>
  );
}

export default App;
