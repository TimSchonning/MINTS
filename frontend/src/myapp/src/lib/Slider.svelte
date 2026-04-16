<script lang="ts">
	import { shown_date, time_resolution } from '../map_controller';

	const now = new Date();
	const elapsedMinutes = now.getHours() * 60 + now.getMinutes();
	const mappedMinutes = Math.round(elapsedMinutes / time_resolution) * time_resolution;
	let sliderMinutes = $state(mappedMinutes);
	let showTooltip = $state(false);

	$effect(() => {
		shown_date.setHours(0, sliderMinutes, 0, 0);
	});

	// 4. A helper to show the formatted time
	const displayTime = $derived(
		shown_date.toLocaleTimeString([], {
			hour: '2-digit',
			minute: '2-digit'
		})
	);
</script>

<div class="slidecontainer">
	{#if showTooltip}
		<div class="tooltip" style="left: {(sliderMinutes / 1425) * 100}%">
			{displayTime}
		</div>
	{/if}

	<input
		id="time-slider"
		type="range"
		min="0"
		max="1425"
		step={time_resolution}
		bind:value={sliderMinutes}
		class="slider"
		onmouseenter={() => (showTooltip = true)}
		onmouseleave={() => (showTooltip = false)}
		onmousedown={() => (showTooltip = true)}
		onmouseup={() => (showTooltip = false)}
	/>
	<div class="slider-ticks">
		{#each Array(24) as _, i}
			<span class="tick" style="left: {(i * 60 / 1425) * 100}%">
				{i}:00
			</span>
		{/each}
	</div>
</div>

<style>
	/* boxen */
	.slider {
		-webkit-appearance: none;
		width: 100%;
		height: 5px;
		border-radius: 5px;
		background: #5a5858;
		outline: none;
		-webkit-transition: 0.2s;
		transition: opacity 0.2s;
	}

	.slider::-webkit-slider-thumb {
		-webkit-appearance: none;
		appearance: none;
		border-radius: 5px;
		width: 10px;
		height: 25px;
		background: #000000;
		cursor: pointer;
	}

	.slider::-moz-range-thumb {
		width: 10px;
		height: 25px;
		background: #000000;
		cursor: pointer;
	}

	/* Tooltip */
	.tooltip {
		position: absolute;
		top: -35px;
		transform: translateX(-50%);

		padding: 4px 8px;
		border-radius: 8px;

		font-size: 12px;
		font-weight: 500;

		background: rgba(0, 0, 0, 0.75);
		color: white;

		pointer-events: none;

		transition:
			opacity 0.2s ease,
			transform 0.2s ease;
	}
	.slider-ticks {
  		display: flex;
  		justify-content: space-between;
  		padding: 0 10px;
	}

	.slider-ticks span {
  		display: flex;
  		justify-content: center;
  		width: 1px;
  		height: 4px;
  		background: #d3d3d3;
  		line-height: 20px;
		font-size: 12px;
	}
	input[type="range"] {
    	width: 100%;
    	margin: 0;
	}
</style>
