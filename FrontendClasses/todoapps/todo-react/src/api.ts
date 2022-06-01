import { Todo } from './todo';

export const loadTodos = (): Promise<Todo[]> =>
  fetch('http://localhost:4000/api/todos')
    .then((res) => res.json());


export const deleteTodo = (todoIdToDelete: string) =>
  fetch(`http://localhost:4000/api/todos/${todoIdToDelete}`, { method: 'DELETE' })
    .then((res) => res.json());


export const updateTodo = (newTodoData: Partial<Todo> & { _id: string }) =>
  fetch(`http://localhost:4000/api/todos/${newTodoData._id
    }`,
    {
      method: 'PUT',
      body: JSON.stringify(newTodoData),
      headers: { 'Content-Type': 'application/json' },
    })
    .then((res) => res.json());


export const addTodo = (todoText: string) => {
  const newTodo = {
    text: todoText,
    done: false,
  }
  return fetch(`http://localhost:4000/api/todos/`,
    {
      headers: { 'Content-Type': 'application/json' },
      method: 'POST',
      body: JSON.stringify(newTodo)
    })
    .then((res) => res.json());
}