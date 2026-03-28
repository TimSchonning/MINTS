<script lang="ts">

    let isPlaying = $state(false);

    function handleClick(event: Event) {
        isPlaying = !isPlaying;
        if (isPlaying) {
            console.log('Playing animation');
            // startAnimation();
        } else {
            console.log('Pausing animation');
            // pauseAnimation();
        }
    }

</script>

<button class="play-button" aria-label="Play/Pause" onclick={handleClick}>
    <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24"><path fill="currentColor" fill-rule="evenodd" d="M22 12c0 5.523-4.477 10-10 10S2 17.523 2 12S6.477 2 12 2s10 4.477 10 10m-5 0L9 7.5v9z" clip-rule="evenodd"/></svg>
</button>