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

<style>
    .play-button {
        background-color: #505050;
        color: rgb(255, 255, 255);
        border: none;
        border-radius: 50%;
        width: 36px;
        height: 36px;
        display: flex;
        align-items: center;
        justify-content: center;
        cursor: pointer;
        font-size: 24px;
        transition: all 0.2s ease;
        box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
    }

    .play-button:hover {
        background-color: #1d2935;
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
        transform: scale(1.05);
    }

    .play-button:active {
        transform: scale(0.95);
    }
</style>