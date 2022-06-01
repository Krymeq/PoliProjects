import React, { useEffect, useState } from 'react';
import { ButtonContainer } from './components/ButtonContainer';
import { Todo } from './todo';
import { addTodo, deleteTodo, loadTodos, updateTodo } from './api';
import { TodoList } from './components/TodoList';
import { NewTodo } from './components/NewTodo';
import "./App.css";

const filterTodos = (mode: number, todos: Todo[]) => {
  switch(mode) {
    case 1:
      return todos.filter((todo) => !todo.done);
    case 2:
      return todos.filter((todo) => todo.done);
    default:
      return todos;
  }
}


function App() {
  const [mode, setMode] = useState(0);
  const [todos, setTodos] = useState<Todo[]>([]);
  useEffect(() => {
    loadTodos().then(setTodos);
  }, [])

  const removeTodo = (todo: Todo) => deleteTodo(todo._id).then(setTodos);
  const addNewTodo = (todoText: string) => addTodo(todoText).then(setTodos);
  const swapTodoStatus = (todo: Todo) => updateTodo({...todo, done: !todo.done}).then(setTodos);

  return (
    <>
      <div className="background" />
      <div className="app">
        <header>
          <h1>TODONOTER</h1>
          <div>Co masz zrobić jutro, zrób pojutrze!</div>
        </header>
        <ButtonContainer 
          mode={mode} 
          setMode={setMode} 
        />
        <TodoList 
          todoList={filterTodos(mode, todos)} 
          swapTodoStatus={swapTodoStatus} 
          deleteTodo={removeTodo} 
        />
        <NewTodo addTodo={addNewTodo} />
      </div>
    </>
  );
}

export default App;
