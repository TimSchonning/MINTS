<script lang="ts">
  import { onMount } from 'svelte';

  interface MapLocation {
    lat: number;
    lng: number;
  }

  let map: google.maps.Map | null = null;
  let error: string | null = $state(null);
  let loading = $state(true);

  const apiKey = import.meta.env.VITE_GOOGLE_MAPS_API_KEY;

  onMount(() => {
    (async () => {
      try {
        console.log('Map component mounting, apiKey present:', !!apiKey);
        
        if (!apiKey) {
          throw new Error(
            'Google Maps API key is not configured. Add VITE_GOOGLE_MAPS_API_KEY to your .env.local file.'
          );
        }

        const mapElement = document.getElementById('map');
        if (!mapElement) {
          throw new Error('Map container element not found');
        }

        // Load the Google Maps API script dynamically
        const script = document.createElement('script');
        script.src = `https://maps.googleapis.com/maps/api/js?key=${apiKey}`;
        script.async = true;
        script.defer = true;
        document.head.appendChild(script);

        // Wait for the script to load
        await new Promise((resolve, reject) => {
          script.onload = resolve;
          script.onerror = reject;
        });

        console.log('Google Maps library loaded');

        const location: MapLocation = { lat: 59.844603, lng: 17.630702 };

        // Use the global google.maps object
        const { Map, Marker } = window.google.maps;

        map = new Map(mapElement, {
          center: location,
          zoom: 15
        });

        new Marker({
          position: location,
          map
        });
    } catch (err) {
      error = err instanceof Error ? err.message : 'Failed to load map';
      console.error('Map initialization error:', err);
    } finally {
      loading = false;
    }
    })();

    return () => {
      map = null;
    };
  });
</script>

{#if loading}
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
{/if}