<script lang="ts">
	import Map from '$lib/Map.svelte';
	import Slider from '$lib/Slider.svelte';
    import Playbutton from '$lib/Playbutton.svelte';
    import Menu from '$lib/Menu.svelte';
</script>

<div style="margin: 0; padding: 0; width: 100vw; height: 100vh; overflow: hidden;">
	<Map />
    <div style="position: fixed; top: 20px; left: 20px; z-index: 10; background-color: rgba(255, 255, 255, 1); opacity: 0.8; border-radius: 20px; padding: 16px;">
        <Menu />
    </div>
	<div style="position: fixed; bottom: 20px; left: 20px; right: 20px; z-index: 10; background-color: rgba(255, 255, 255, 1); opacity: 0.8; height: 40px; border-radius: 20px; padding: 16px; box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15); display: flex; gap: 20px; align-items: center;">
		<div style="position: relative; z-index: 11;">
			<Playbutton/>
		</div>
		<div style="flex: 1; min-width: 0;">
			<Slider/>
		</div>
	</div>
</div>

<style>
	:global(body) {
		margin: 0;
		padding: 0;
		overflow: hidden;
	}

	:global(html) {
		margin: 0;
		padding: 0;
	}
</style>
