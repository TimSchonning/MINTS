<script lang="ts">
	let {
		station_id,
		noise = 0,
		pm25 = 0,
		pm5 = 0
	} = $props<{
		station_id: string | undefined;
		noise?: number; // Added with ? for optional
		pm25?: number; // Added with ? for optional
		pm5?: number; // Added with ? for optional
	}>();
</script>

<div class="marker">
	<h3>{`Station: ${station_id ?? 'Unknown'}`}</h3>
	<ul>
		<li>Noise: {noise}</li>
		<li>PM2.5: {pm25}</li>
		<li>PM5: {pm5}</li>
	</ul>
</div>

<style>
	.marker {
		background-color: #fff;
		border: 1px solid #ccc;
		border-radius: 4px;
		padding: 8px;
		font-size: 12px;
		color: #333;
		box-shadow: 0 2px 6px rgba(0, 0, 0, 0.3);
	}

	.marker h3 {
		margin: 0 0 4px;
		font-size: 14px;
	}

	.marker ul {
		list-style: none;
		padding: 0;
		margin: 0;
	}

	.marker li {
		margin-bottom: 2px;
	}
</style>
