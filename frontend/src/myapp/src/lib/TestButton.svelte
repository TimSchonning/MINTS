<script lang="ts">
	import { create_station } from '@my-app/database';

	let isAdded: boolean = $state(false);
	async function testStoringStation() {
		console.log('Attempting to create a station');

		await create_station((1).toString(), { lat: 2, lng: 4 });
		isAdded = true;
	}
</script>

{#if isAdded}
	<h1>A station has been added to the database!</h1>
{:else}
	<button onclick={testStoringStation} style="cursor: pointer;">
		Click me to test adding a station to firebase
	</button>
{/if}
