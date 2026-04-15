<script lang="ts">
	import { shown_date, time_resolution } from '../map_controller';

	const now = new Date();
	const elapsedMinutes = now.getHours() * 60 + now.getMinutes();
	const mappedMinutes = Math.round(elapsedMinutes / time_resolution) * time_resolution;
	let sliderMinutes = $state(mappedMinutes);

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
	<label for="time-slider">Select Time (15m intervals):</label>
	<input
		id="time-slider"
		type="range"
		min="0"
		max="1425"
		step="15"
		bind:value={sliderMinutes}
		class="slider"
	/>

	<p>Selected Time: <strong>{displayTime}</strong></p>
	<p><small>Raw Minutes: {sliderMinutes}</small></p>
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
</style>
