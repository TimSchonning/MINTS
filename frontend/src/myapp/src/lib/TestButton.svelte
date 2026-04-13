<script lang="ts">
	import {
		create_station,
		create_measurement,
		create_sensor_type,
		get_all_stations,
		Interval,
		get_measurements_in_interval
	} from '@my-app/database';
	import { load_interval, sensor_type_map } from '../map_controller';

	let isStationAdded: boolean = $state(false);
	let isMeasurementAdded: boolean = $state(false);
	let isSensorTypeAdded: boolean = $state(false);
	async function testStoringStation() {
		console.log('Attempting to create a station');

		await create_station((1).toString(), { lat: 2, lng: 4 });
		isStationAdded = true;
	}

	async function testStoreMeasurement() {
		console.log('Attempting to create a measurement');

		await create_measurement('1', '1', 'PM2.5', 5.3, new Date(2010, 2, 4));
		isMeasurementAdded = true;
	}

	async function testStoringSensorType() {
		console.log('Attempting to create a sensor type');

		await create_sensor_type('PM5', 100, 520);
		isSensorTypeAdded = true;
	}

	async function fetchStations() {
		console.log('Attempting to fetch sensors');

		let stations = await get_all_stations();
		stations.forEach((station) => {
			console.log(station.toString());
		});
	}

	async function fetchMeasurementsInInterval() {
		console.log('Attempting to fetch measurement data for an interval');

		let interval = new Interval(new Date(2000), new Date(2030, 0, 0));
		let measurements = await get_measurements_in_interval(interval);
		measurements.forEach((measurement) => {
			console.log(measurement.toString());
		});

		console.log('Fetching done!');
	}

	async function loadInterval() {
		console.log('Attempting to fetch measurement data for an interval');

		let interval = new Interval(new Date(2000), new Date(2030, 0, 0));
		let stations = await load_interval(interval);
		stations.forEach((station) => {
			console.log(station.toString());
		});

		console.log('Fetching done!');
	}

	async function printSensorTypes() {
		const sensor_types = sensor_type_map.values().toArray();
		sensor_types.forEach((sensor_type) => {
			console.log(sensor_type.toString());
		});
	}
</script>

{#if isStationAdded}
	<h1>A station has been added to the database!</h1>
{:else}
	<button onclick={testStoringStation} style="cursor: pointer;">
		Click me to test adding a station to firebase
	</button>
{/if}
{#if isMeasurementAdded}
	<h1>A measurement has been added to the database!</h1>
{:else}
	<button onclick={testStoreMeasurement} style="cursor: pointer;">
		Click me to test adding a measurement to firebase
	</button>
{/if}

{#if isSensorTypeAdded}
	<h1>A sensor type has been added to the database!</h1>
{:else}
	<button onclick={testStoringSensorType} style="cursor: pointer;">
		Click me to test adding a sensor type to firebase
	</button>
{/if}

<button onclick={fetchStations} style="cursor: pointer;"> Fetch all stations </button>
<button onclick={fetchMeasurementsInInterval} style="cursor: pointer;">
	Fetch measurements in interval
</button>

<button onclick={loadInterval} style="cursor: pointer;">
	Load stations with measurements for interval</button
>
<button onclick={printSensorTypes} style="cursor: pointer;"> Print all sensor types</button>
