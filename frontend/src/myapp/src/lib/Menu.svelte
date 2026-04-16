<script lang="ts">
	import { addLayer, removeLayer } from '../heatmap';

	let menuItems = [
		{
			name: 'Noise',
			displayText: 'Noise',
			checked: true
		},
		{
			name: 'PM2.5',
			displayText: 'PM2.5',
			checked: true
		},
		{
			name: 'PM10',
			displayText: 'PM10',
			checked: true
		}
	];

	let showMenu = $state(true);
	let content;

	function handleClick(event: Event) {
		showMenu = !showMenu;
	}
	function handleToggle(item: any) {
		if (item.checked) {
			addLayer(item.name);
		} else {
			removeLayer(item.name);
		}
	}
</script>

<div class="menu-wrapper">
	<button class="content" onclick={handleClick}> menu </button>

	<div class="navbar {showMenu ? 'open' : ''}">
		<ul>
			{#each menuItems as item}
				<li>
					<label>
						{item.displayText}
						<input
							type="checkbox"
							bind:checked={item.checked}
							onchange={() => handleToggle(item)}
						/>
					</label>
				</li>
			{/each}
		</ul>
	</div>
</div>

<style>
	button.content {
		all: unset;

		font-weight: 500;
		cursor: pointer;

		transition: all 0.25s ease;
	}

	.navbar {
		background: rgba(255, 255, 255, 0.15);
		backdrop-filter: blur(18px);

		overflow: hidden;

		/* collapsed state */
		max-height: 0;
		opacity: 0;
		transform: scale(0.95);

		transition:
			max-height 0.35s ease,
			opacity 0.25s ease,
			transform 0.25s ease;
	}

	.navbar.open {
		max-height: 300px;
		opacity: 1;
		transform: scale(1);
	}

	.navbar ul {
		list-style: none;
		margin: 0;
	}

	.navbar label {
		display: flex;
		justify-content: space-between;
		align-items: center;

		padding: 7px 5px;
		cursor: pointer;

		font-size: 14px;
		font-weight: 500;
		color: rgba(0, 0, 0, 0.9);
	}

	.navbar input[type='checkbox'] {
		appearance: none;
		width: 18px;
		height: 18px;

		border-radius: 6px;
		border: 1px solid rgba(0, 0, 0, 0.6);

		position: relative;
		cursor: pointer;
		margin-left: 2px;

		transition: all 0.2s ease;
	}

	.navbar input[type='checkbox']:checked {
		background: rgba(82, 88, 94, 0.9);
		border: none;
	}

	.navbar input[type='checkbox']:checked::after {
		content: '';
		position: absolute;
		top: 3px;
		left: 6px;

		width: 4px;
		height: 8px;

		border: solid white;
		border-width: 0 2px 2px 0;
		transform: rotate(45deg);
	}
</style>
