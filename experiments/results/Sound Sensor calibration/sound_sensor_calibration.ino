/*
  Sound Sensor RMS + Approximate dB Meter
  Reads analog microphone sensor from A0

  Works with:
  - KY-037
  - KY-038
  - MAX4466
  - similar analog microphone modules
*/

const int SOUND_PIN = A0;

// Sampling settings
const int SAMPLE_WINDOW_MS = 200;   // 100 ms window
const int ADC_MAX = 4095;           // Arduino Uno/Nano
// Use 4095 for ESP32

void setup() {
  Serial.begin(115200);
}

void loop() {

  unsigned long startMillis = millis();

  long signalMin = ADC_MAX;
  long signalMax = 0;

  // Collect samples for 100 ms
  while (millis() - startMillis < SAMPLE_WINDOW_MS) {

    int sample = analogRead(SOUND_PIN);

    if (sample < signalMin) {
      signalMin = sample;
    }

    if (sample > signalMax) {
      signalMax = sample;
    }
  }

  // Peak-to-peak amplitude
  int peakToPeak = signalMax - signalMin;

  // Normalize
  float voltage = (peakToPeak * 3.3) / ADC_MAX;

  // Approximate decibel calculation
  // Adjust this calibration factor experimentally
  float dB = 25 * log10(voltage / 0.00175); // Fungerar okej mellan 30-72 dB

  // Prevent negative infinity
  if (voltage <= 0.01) {
    dB = 0;
  }

  Serial.print("Min: ");
  Serial.print(signalMin);

  Serial.print("  Max: ");
  Serial.print(signalMax);

  Serial.print("  Peak-Peak: ");
  Serial.print(peakToPeak);

  Serial.print("  Voltage: ");
  Serial.print(voltage, 3);

  Serial.print(" V  Approx dB: ");
  Serial.println(dB, 1);

  delay(200);
}