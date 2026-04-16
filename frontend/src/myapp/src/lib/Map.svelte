<script lang="ts">
	import { onMount } from 'svelte';
	import mapboxgl from 'mapbox-gl';
	import 'mapbox-gl/dist/mapbox-gl.css';
	import { toGeoJSON, testData, Data, show_heatmap } from '../heatmap.ts';
	import { shown_date } from '../map_controller.ts';

	let map: mapboxgl.Map;

	$effect(() => {
		show_heatmap(shown_date);
	});

	onMount(() => {
		mapboxgl.accessToken = import.meta.env.VITE_MAPBOX_ACCESS_TOKEN;
		map = new mapboxgl.Map({
			container: 'map',
			style: 'mapbox://styles/mapbox/standard',
			center: [17.635488, 59.843905],
			zoom: 12
		});

		map.addControl(new mapboxgl.NavigationControl());

		map.on('load', () => {
			map.addSource('heat', {
				type: 'geojson',
				data: toGeoJSON([])
			});

			map.addLayer({
				id: 'heatmap',
				type: 'heatmap',
				source: 'heat',
				maxzoom: 20,
				paint: {
					'heatmap-weight': ['interpolate', ['linear'], ['get', 'intensity'], 0, 0, 1, 4],
					'heatmap-radius': ['interpolate', ['linear'], ['get', 'intensity'], 0, 20, 1, 50]
				}
			});
			testData.subscribe((data) => {
				const source = map.getSource('heat') as mapboxgl.GeoJSONSource;
				if (source) {
					source.setData(toGeoJSON(data));
				}
			});
		});
	});
</script>

<div id="map" style="width: 100vw; height: 100vh;"></div>
