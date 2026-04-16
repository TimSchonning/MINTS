<script lang="ts">
	import { shown_date } from '../map_controller';

	let { station_id, is_open, noise, pm25, pm5 } = $props<{
		station_id: string | undefined;
		is_open: boolean;
		noise?: number; // Added with ? for optional
		pm25?: number; // Added with ? for optional
		pm5?: number; // Added with ? for optional
	}>();

	$effect(() => {
		const date = shown_date;
		if (is_open) {
			console.log(date);
			console.log(`Update popup station: ${station_id}`);
		}
	});
</script>

<div class="marker_popup">
	<h3>{`Station: ${station_id ?? 'Unknown'}`}</h3>
	<ul>
		<li>Noise: {noise ?? 'No data'}</li>
		<li>PM2.5: {pm25 ?? 'No data'}</li>
		<li>PM5: {pm5 ?? 'No data'}</li>
	</ul>
</div>

<style>
	.marker_popup {
		background-color: #fff;
		border: 1px solid #ccc;
		border-radius: 4px;
		padding: 8px;
		font-size: 12px;
		color: #333;
		box-shadow: 0 2px 6px rgba(0, 0, 0, 0.3);
	}

	.marker_popup h3 {
		margin: 0 0 4px;
		font-size: 14px;
	}

	.marker_popup ul {
		list-style: none;
		padding: 0;
		margin: 0;
	}

	.marker_popup li {
		margin-bottom: 2px;
	}
</style>
