<script lang="ts">
	import type { SensorType } from '@my-app/database';
	import { get_sensor_types, shown_date, timelapse_controller } from '../map_controller';
	import { SvelteMap } from 'svelte/reactivity';

	interface AvgStats {
		sensor_type: SensorType;
		avg_value: number | undefined;
	}

	function calc_severity(stats: AvgStats): string | undefined {
		if (stats.avg_value == undefined) {
			return;
		}

		const percentage = stats.sensor_type.calc_severity(stats.avg_value);
		if (percentage < 0.3) {
			return 'Low';
		} else if (percentage < 0.6) {
			return 'Medium';
		} else if (percentage < 0.9) {
			return 'High';
		} else {
			return 'Severe';
		}
	}

	const measurement_stats: SvelteMap<string, AvgStats> = new SvelteMap();

	let { station_id, is_open, noise, pm25, pm5 } = $props<{
		station_id: string | undefined;
		is_open: boolean;
		noise?: number | undefined; // Added with ? for optional
		pm25?: number | undefined; // Added with ? for optional
		pm5?: number | undefined; // Added with ? for optional
	}>();

	$effect(() => {
		const load_task = async () => {
			const date = shown_date;
			if (is_open) {
				let data = await timelapse_controller.get_measurement_data(date);
				measurement_stats.clear();
				for (let index = 0; index < data.length; index++) {
					const station = data[index];
					if (station.id == station_id) {
						const avg_values = station.calc_avg_measurements();
						const sensor_types = get_sensor_types();
						sensor_types.forEach((sensor_type) => {
							let stats: AvgStats = {
								sensor_type: sensor_type,
								avg_value: avg_values.get(sensor_type.sensor_id)
							};
							measurement_stats.set(sensor_type.sensor_id, stats);
						});
						break;
					}
				}
				console.log(`Update popup station: ${station_id}`);
			}
		};
		load_task();
	});
</script>

<div class="marker_popup">
	<h3>{`Station: ${station_id ?? 'Unknown'}`}</h3>
	<ul>
		{#each measurement_stats.values() as stats: AvgStats}
			{@const severity = calc_severity(stats)}
			<li class="sensor-row">
				<div>
					{stats.sensor_type.sensor_id}: {stats.avg_value ? `${stats.avg_value}` : 'No data'}
				</div>
				{#if severity}
					<span class={severity.toLowerCase()}>
						{severity}
					</span>
				{/if}
			</li>
		{/each}
	</ul>
</div>

<style>
	.severe {
		color: rgb(0, 0, 0);
		font-weight: bold;
	}
	.high {
		color: rgb(241, 0, 0);
		font-weight: bold;
	}
	.medium {
		color: orange;
	}
	.low {
		color: green;
	}
	.sensor-row {
		display: flex;
		align-items: center;
		justify-content: space-between;
		gap: 10px;
		padding: 8px 0;
		border-bottom: 1px solid #eee;
	}
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
