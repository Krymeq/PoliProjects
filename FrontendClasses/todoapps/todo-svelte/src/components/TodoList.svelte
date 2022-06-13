<script lang="ts">
	import type { Todo } from 'src/todo';
	
	export let todos: Todo[];
	export let swapTodoStatus: (todo: Todo) => void;
	export let deleteTodo: (todo: Todo) => void;
</script>

<div class="todo-container">
	{#each todos as todo}
		<div class={`todo-item ${todo.done ? 'completed' : ''}`}>
			<span>
				{todo.text}
			</span>
			<div class="icon-panel">
				<button class="icon" on:click={() => swapTodoStatus(todo)}>
					{#if todo.done}
						<img src="/assets/cross-svgrepo-com.svg" alt="x"/>
					{:else}
						<img src="/assets/tick-svgrepo-com.svg" alt="ok" />
					{/if}
				</button>
				<button class="icon" on:click={() => deleteTodo(todo)}>
					<img src="/assets/trash.svg" alt="delete" />
				</button>
			</div>
		</div>
	{/each}
</div>

<style>
	.todo-container {
		max-width: 1200px;
		padding: 20px;
		margin: 0px auto;
	}
	.todo-container .todo-item {
		display: flex;
		justify-content: space-between;
		backdrop-filter: blur(2px);
		margin-bottom: 15px;
		color: #dfdfdf;
		font-size: 1.2em;
		border-radius: 10px;
		border: 2px solid #dfdfdf;
		padding: 10px 15px;
	}

	.todo-container .completed {
		background-color: rgba(0, 180, 140, 0.8);
	}

	.icon {
		height: 26px;
		width: 26px;
		outline: none;
		border: none;
		background-color: transparent;
		transition: background-color 0.13s ease-in;
		display: flex;
		justify-content: center;
		align-items: center;
		border-radius: 3px;
	}

	.icon img {
		height: 100%;
		width: 100%;
	}

	.icon:hover {
		cursor: pointer;
		background-color: #5f4592;
	}

	.icon-panel {
		display: flex;
		gap: 4px;
	}
</style>
