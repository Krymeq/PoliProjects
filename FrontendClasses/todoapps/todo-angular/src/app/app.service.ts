import { Injectable } from "@angular/core";
import { Todo } from "./todo";

@Injectable({ providedIn: 'root' })
export class AppService {
  todos: Todo[] = [];

  loadTodos() {
    fetch('http://localhost:4000/api/todos')
      .then((res) => res.json())
      .then((res) => { this.todos = res });
  }

  deleteTodo(todoIdToDelete: string) {
    fetch(`http://localhost:4000/api/todos/${todoIdToDelete}`, { method: 'DELETE' })
      .then(() => {
        this.todos = this.todos.filter((todo) => todo._id !== todoIdToDelete)
      });
  }

  updateTodo(newTodoData: Partial<Todo> & { _id: string }) {
    fetch(`http://localhost:4000/api/todos/${newTodoData._id}`,
      {
        method: 'PUT',
        body: JSON.stringify(newTodoData),
        headers: { 'Content-Type': 'application/json' },
      })
      .then((res) => res.json())
      .then((res) => {
        this.todos = res;
      });
  }

  addTodo(todoText: string) {
    console.log(todoText);
    const newTodo = {
      text: todoText,
      done: false,
    }
    fetch(`http://localhost:4000/api/todos/`,
      {
        headers: { 'Content-Type': 'application/json' },
        method: 'POST',
        body: JSON.stringify(newTodo)
      })
      .then((res) => res.json())
      .then((res) => this.todos = res);
  }
};
