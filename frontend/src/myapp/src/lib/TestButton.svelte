<script lang="ts">
	import {
		create_station,
		create_measurement,
		create_sensor_type,
		get_all_stations
	} from '@my-app/database';

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

		await create_measurement('1', '1', 'PM2.5', 5.3, new Date(10, 2, 4));
		isMeasurementAdded = true;
	}

	async function testStoringSensorType() {
		console.log('Attempting to create a sensor type');

		await create_sensor_type('PM2.5', 1, 5);
		isSensorTypeAdded = true;
	}

	async function fetchStations() {
		console.log('Attempting to fetch sensors');

		let stations = await get_all_stations();
		stations.forEach((station) => {
			console.log(station.toString());
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
