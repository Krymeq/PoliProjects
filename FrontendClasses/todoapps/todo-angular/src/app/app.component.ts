import { Component, OnInit } from '@angular/core';
import { AppService } from './app.service';
import { Todo } from './todo';

@Component({
  selector: 'app-root',
  template: `
  <ng-container>
    <div class="background"></div>
    <div class="app">
      <header>
        <h1>TODONOTER</h1>
        <div>Co masz zrobić jutro, zrób pojutrze!</div>
      </header>
      <div class="button-panel">
        <button (click)="this.setMode(0)" [ngClass]="this.mode === 0 ? 'selected' : ''">Wszystkie</button>
        <button (click)="this.setMode(1)" [ngClass]="this.mode === 1 ? 'selected' : ''">W trakcie</button>
        <button (click)="this.setMode(2)" [ngClass]="this.mode === 2 ? 'selected' : ''">Ukończone</button>
      </div>

      <div class="todo-container">
        <div 
          *ngFor="let todo of this.getFilteredTodos()"
          class="todo-item"
          [ngClass]="todo.done ? 'completed' : ''"
        >
          <span>{{todo.text}}</span>
          <div class="icon-panel">
            <button *ngIf="!todo.done" class="icon" (click)="this.swapTodoStatus(todo)">
              <img src="/assets/tick-svgrepo-com.svg">
            </button>
            <button *ngIf="todo.done" class="icon" (click)="this.swapTodoStatus(todo)">
              <img src="/assets/cross-svgrepo-com.svg">
            </button>
            <button class="icon" (click)="this.deleteTodo(todo)">
              <img src="/assets/trash.svg">
            </button>
          </div>
        </div>
      </div>
      
      <div class="add-todo-container">
        <input [(ngModel)]="this.newTodo" placeholder="Co chciał(a)byś zrobić?">
        <button (click)="this.addTodo()" [disabled]="this.newTodo.length === 0">Dodaj</button>
      </div>
    </div>
  </ng-container>
  `,
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
  constructor(public appService: AppService) { }
  mode: number = 0;
  newTodo: string = '';

  ngOnInit(): void {
    this.appService.loadTodos();
  }

  getFilteredTodos(): Todo[] {
    switch(this.mode) {
      case 1:
        return this.appService.todos.filter((todo) => !todo.done);
      case 2:
        return this.appService.todos.filter((todo) => todo.done);
      default:
        return this.appService.todos;
    }
  }

  addTodo(): void {
    this.appService.addTodo(this.newTodo);
    this.newTodo = '';
  }

  setMode(mode: number) {
    this.mode = mode;
  }

  swapTodoStatus(todo: Todo): void {
    this.appService.updateTodo({...todo, done: !todo.done});
  }

  deleteTodo(todo: Todo): void {
    this.appService.deleteTodo(todo._id);
  }
}
