<script lang="ts">
    let station_id: string;
    let noise: number;
    let pm25: number;
    let pm5: number;
</script>

<div class= "marker">
    <h3>{station_id}</h3>
    <ul>
        <li>Noise: {noise}</li>
        <li>PM2.5: {pm25}</li>
        <li>PM5: {pm5}</li>
    </ul>
</div>

<style>
    .marker {
        background-color: #fff;
        border: 1px solid #ccc;
        border-radius: 4px;
        padding: 8px;
        font-size: 12px;
        color: #333;
        box-shadow: 0 2px 6px rgba(0, 0, 0, 0.3);
    }

    .marker h3 {
        margin: 0 0 4px;
        font-size: 14px;
    }

    .marker ul {
        list-style: none;
        padding: 0;
        margin: 0;
    }

    .marker li {
        margin-bottom: 2px;
    }     
</style>