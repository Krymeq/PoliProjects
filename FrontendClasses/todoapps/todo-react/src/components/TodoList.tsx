import { Todo } from "../todo";
import "./styles/TodoList.css";

interface ListProps {
  todoList: Todo[];
  swapTodoStatus: (todo: Todo) => void;
  deleteTodo: (todo: Todo) => void;
}

interface ItemProps {
  todo: Todo;
  swapTodoStatus: (todo: Todo) => void;
  deleteTodo: (todo: Todo) => void;
}

const TodoItem: React.FC<ItemProps> = ({ todo, swapTodoStatus, deleteTodo }) => {
  return (
    <div className={`todo-item ${todo.done ? 'completed' : ''}`}>
      <span>
        {todo.text}
      </span>
      <div className="icon-panel">
        <button className="icon" onClick={() => swapTodoStatus(todo)}>
          { todo.done
            ? <img src="/assets/cross-svgrepo-com.svg" alt="x" />
            : <img src="/assets/tick-svgrepo-com.svg" alt="ok" />
          }
        </button>
        <button className="icon" onClick={() => deleteTodo(todo)}>
          <img src="/assets/trash.svg" alt="delete" />
        </button>
      </div>
    </div>
  )
}

export const TodoList: React.FC<ListProps> = ({ todoList, swapTodoStatus, deleteTodo }) => {
  return (
    <div className="todo-container">
      {todoList.map((todo, index) =>
        <TodoItem key={index} todo={todo} deleteTodo={deleteTodo} swapTodoStatus={swapTodoStatus} />
      )}
    </div>
  )
}