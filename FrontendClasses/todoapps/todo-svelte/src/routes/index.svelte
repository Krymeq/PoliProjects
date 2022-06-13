<script lang="ts">
	import { addTodo, deleteTodo, loadTodos, updateTodo } from '../api';
	import type { Todo } from '../todo';
	import ButtonContainer from '../components/ButtonContainer.svelte';
	import TodoList from '../components/TodoList.svelte';
	import NewTodo from '../components/NewTodo.svelte';

	const filterTodos = (filterMode: number, todoList: Todo[]) => {
		switch (filterMode) {
			case 1:
				return todoList.filter((todo) => !todo.done);
			case 2:
				return todoList.filter((todo) => todo.done);
			default:
				return todoList;
		}
	};

	let mode = 0;
	let todos: Todo[] = [];
	$: filteredTodos = filterTodos(mode, todos);

	loadTodos().then((newTodos) => (todos = newTodos));

	const removeTodo = (todo: Todo) => {
		deleteTodo(todo._id).then((newTodos) => (todos = newTodos));
	};

	const swapTodoStatus = (todo: Todo) =>
		updateTodo({ ...todo, done: !todo.done }).then((newTodos) => (todos = newTodos));

	const createTodo = (todoText: string) =>
		addTodo(todoText).then((newTodos) => {
			todos = newTodos;
		});
</script>

<div class="background" />
<div class="app">
	<header>
		<h1>TODONOTER</h1>
		<div>Co masz zrobić jutro, zrób pojutrze!</div>
	</header>
	<ButtonContainer bind:mode={mode} />
	<TodoList todos={filteredTodos} deleteTodo={removeTodo} {swapTodoStatus} />
	<NewTodo {createTodo} />
</div>

<style>
	header {
		display: flex;
		flex-direction: column;
		align-items: center;
		margin-bottom: 20px;
	}
	header > div {
		color: #599acf;
	}

	header > h1 {
		color: #dfdfdf;
		margin-bottom: 2px;
	}

	.app {
		position: relative;
		z-index: 200;
	}

	.background {
		z-index: 0;
		position: fixed;
		display: block;
		height: 100vh;
		width: 100vw;
		background: linear-gradient(135deg, #2f3061 0%, #343434 100%);
		content: '';
	}
</style>
