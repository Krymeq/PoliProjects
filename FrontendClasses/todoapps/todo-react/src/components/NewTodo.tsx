import React, { useState } from "react";
import "./styles/NewTodo.css";

interface Props {
  addTodo: (newTodoText: string) => void;
}

export const NewTodo: React.FC<Props> = ({addTodo}) => {
  const [newTodoText, setNewTodoText] = useState('');
  const handleClick = () => {
    addTodo(newTodoText);
    setNewTodoText('');
  }

  return (
    <div className="add-todo-container">
      <input 
        value={newTodoText} 
        onChange={e => setNewTodoText(e.target.value)} 
        placeholder="Co chciał(a)byś zrobić?" />
      <button onClick={handleClick} disabled={newTodoText.length === 0}>Dodaj</button>
    </div>
  )
}