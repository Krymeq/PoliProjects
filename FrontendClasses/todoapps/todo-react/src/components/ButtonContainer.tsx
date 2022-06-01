import React from 'react';
import './styles/ButtonContainer.css';

interface Props {
  mode: number;
  setMode: (mode: number) => void;
}

export const ButtonContainer: React.FC<Props> = ({ mode, setMode }) => {
  return (
    <div className="button-panel">
      <button onClick={() => setMode(0)} className={mode === 0 ? 'selected' : ''} >Wszystkie</button>
      <button onClick={() => setMode(1)} className={mode === 1 ? 'selected' : ''} >W trakcie</button >
      <button onClick={() => setMode(2)} className={mode === 2 ? 'selected' : ''} >Ukończone</button >
    </div >
  )
}