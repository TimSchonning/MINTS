<script lang="ts">
	import { mount, onMount } from 'svelte';
	import mapboxgl from 'mapbox-gl';
	import 'mapbox-gl/dist/mapbox-gl.css';
	import { toGeoJSON, testData, Data, show_heatmap } from '../heatmap.ts';
	import { shown_date } from '../map_controller.ts';
	import { get_all_stations, Station } from '@my-app/database';
	import Marker from './Marker.svelte';
	import Popup from './Popup.svelte';

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

		map.on('load', async () => {
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
					'heatmap-radius': ['interpolate', ['linear'], ['get', 'intensity'], 0, 30, 1, 50]
				}
			});

			Data.subscribe(async (data) => {
				const source = map.getSource('heat') as mapboxgl.GeoJSONSource;
				if (source) {
					source.setData(toGeoJSON(data));
				}
			});

			const station_list: Station[] = await get_all_stations();
			station_list.forEach((station) => {
				const marker_container = document.createElement('div');
				mount(Marker, {
					target: marker_container
				});
				const marker = new mapboxgl.Marker({ element: marker_container })
					.setLngLat([station.position.longitude, station.position.latitude])
					.addTo(map);

				const popup_container = document.createElement('div');
				mount(Popup, { target: popup_container, props: { station_id: station.id } });
				marker.setPopup(new mapboxgl.Popup({ offset: 25 }).setDOMContent(popup_container));
			});
		});
	});
</script>

<div id="map" style="width: 100vw; height: 100vh;"></div>
