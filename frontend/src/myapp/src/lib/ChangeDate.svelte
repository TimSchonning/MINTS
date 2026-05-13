<script lang="ts">
	import ChevronLeftIcon from '@lucide/svelte/icons/chevron-left';
	import ChevronRightIcon from '@lucide/svelte/icons/chevron-right';
	import { shown_date } from '../map_controller';

	function handleClickLeft() {
		shown_date.setDate(shown_date.getDate() - 1);
	}
	function handleClickRight() {
		if (shown_date.getDate() === new Date().getDate()) {
			return;
		} else {
			shown_date.setDate(shown_date.getDate() + 1);
		}
	}
</script>

<div class="inline-flex -space-x-px rounded-full shadow-2xs rtl:space-x-reverse">
	<button
		onclick={handleClickLeft}
		class="rounded-none shadow-none first:rounded-s-full last:rounded-e-full focus-visible:z-10"
		aria-label="Left"
	>
		<ChevronLeftIcon size={16} aria-hidden="true" />
	</button>
	<button class="bg-primary text-primary-foreground flex items-center px-1 text-sm font-medium">
		{shown_date.toLocaleDateString('en-GB', { month: 'long', day: 'numeric', year: 'numeric' })}
	</button>
	<button
		onclick={handleClickRight}
		class="rounded-none shadow-none first:rounded-s-full last:rounded-e-full focus-visible:z-10"
		aria-label="Right"
	>
		<ChevronRightIcon size={16} aria-hidden="true" />
	</button>
</div>

<style>
</style>
