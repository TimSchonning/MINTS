const int SOUND_PIN = A0;

// Sampling settings
const int SAMPLE_WINDOW_MS = 100;   // 100 ms window
const int ADC_MAX = 4095;  // Analog signal is in interval 0-4095

float db_from_peak_to_peak(int peak_to_peak) {
  // Converts the peak-to-peak value into dB using a function fitted using manual calibration. 
  // The functions and calibration data used for this can be found in experiments/results/sound_sensor_calibration
  // This works pretty well in between 30-70 dB, generally being +-5 dB.
  // The largest discrepancies are around 50 dB (see CalibrationPlot.png).
  float a = -13.838529669252635;
  float b = 10.849420757521935;
  float db_approx = a+b*log((float)peak_to_peak);
  return db_approx;
}

float sample_approximate_db_reading() {
  unsigned long startMillis = millis();

  long signalMin = ADC_MAX;
  long signalMax = 0;

  while (millis() - startMillis < SAMPLE_WINDOW_MS) {

    int sample = analogRead(SOUND_PIN);

    if (sample < signalMin) {
      signalMin = sample;
    }

    if (sample > signalMax) {
      signalMax = sample;
    }
  }

  int peakToPeak = signalMax - signalMin;
  float voltage = (peakToPeak * 3.3) / ADC_MAX;

  Serial.print("Peak to peak: ");
  Serial.println(peakToPeak);

  float db_approx = db_from_peak_to_peak(peakToPeak);
  return db_approx;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  float dB = sample_approximate_db_reading();
  Serial.print("Approx dB: ");
  Serial.print(dB);
  Serial.println(" dB");

  delay(200);
}