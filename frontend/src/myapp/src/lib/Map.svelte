<script lang="ts">
  import { onMount } from 'svelte';
  import mapboxgl from 'mapbox-gl';
  import 'mapbox-gl/dist/mapbox-gl.css';

  let map : mapboxgl.Map;

  onMount(() => {
      mapboxgl.accessToken = import.meta.env.VITE_MAPBOX_ACCESS_TOKEN;

      map = new mapboxgl.Map({
          container: 'map',
          style: 'mapbox://styles/mapbox/standard',
          // style: 'mapbox://styles/mapbox/streets-v11',
          // style: 'mapbox://styles/mapbox/dark-v11',
          // style: 'mapbox://styles/mapbox/light-v11',
          center: [17.635488, 59.843905],
          zoom: 12
      });

      map.addControl(new mapboxgl.NavigationControl());
      
      map.on('style.load', () => {
          map.setFog({}); // Set the default atmosphere style
      });
  });

</script>

<!-- {#if loading}
  <div id="map" style="width: 100vw; height: 100vh; display: flex; align-items: center; justify-content: center;">
    <p>Loading map...</p>
  </div>
{:else if error}
  <div id="map" style="width: 100vw; height: 100vh; display: flex; align-items: center; justify-content: center; background-color: #f3f4f6;">
    <div style="text-align: center; padding: 20px;">
      <p style="color: #ef4444; font-weight: bold;">Error loading map</p>
      <p style="color: #666; font-size: 14px;">{error}</p>
    </div>
  </div>
{:else}
  <div id="map" style="width: 100vw; height: 100vh;"></div>
{/if} -->

<div id="map" style="width: 100vw; height: 100vh;"></div>