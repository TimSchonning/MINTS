<script lang="ts"></script>

<div class="slidecontainer">
  <input type="range" min="0" max="1440" value="1440" class="slider" id="myRange">
</div>

<style>
/* boxen */
   .slider {
  -webkit-appearance: none;
  width: 100%;
  height: 5px;
  border-radius: 5px;  
  background: #5a5858;
  outline: none;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  border-radius: 5px;
  width: 10px;
  height: 25px;
  background: #000000;
  cursor: pointer;
}

.slider::-moz-range-thumb {
width: 10px;
height: 25px;
background: #000000;
cursor: pointer;
}
</style>

