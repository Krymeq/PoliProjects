<div class="button-panel">
  <button on:click={() => {mode = 0}} class={mode === 0 ? 'selected' : ''}>Wszystkie</button>
  <button on:click={() => {mode = 1}} class={mode === 1 ? 'selected' : ''}>W trakcie</button>
  <button on:click={() => {mode = 2}} class={mode === 2 ? 'selected' : ''}>Ukończone</button>
</div>

<script lang='ts'>
  export let mode: number;
</script>

<style>
	.button-panel {
		display: flex;
		justify-content: center;
		gap: 10px;
		padding-bottom: 2px;
	}

	.button-panel > button {
		padding: 12px 20px;
		font-size: 1.1em;
		outline: none;
		background-color: transparent;
		color: #dfdfdf;
		border: none;
		transition: background-color 0.13s ease-in;
	}

	.button-panel > button:hover {
		cursor: pointer;
		background-color: #5f4592;
	}

	.button-panel > button.selected {
		border-bottom: 2px solid #dfdfdf;
	}
</style>
