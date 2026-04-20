<script lang="ts">
	import RadioReceiver from '@lucide/svelte/icons/radio-receiver';
</script>

<div class="marker">
	<RadioReceiver size={25} color="black"></RadioReceiver>
</div>

<style>
	.marker {
		display: flex;
		align-items: center;
		justify-content: center;
		width: 25px;
		height: 25px;
		border-radius: 50%;
		cursor: pointer;
	}
</style>
