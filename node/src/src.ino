#include "master.h"

HM330X particle_sensor;
uint8_t     ps_sensor_buf[30];

ps_result_t ps_result;
ns_state_t  ns_state;
ns_result_t ns_result;

RTC_DATA_ATTR payload_t payload;
SX1262 radio = new Module(PIN_CS, PIN_DIO1, PIN_RST, PIN_BSY);

void setup() {
    power_down_radios();
    delay(1000);
    
    DEBUG_BEGIN(BAUD);
    delay(1000);
    
    DEBUG_PRINTLN("[START]");
    
    if (particle_sensor.init())  error_handler(-1, true, PS_INIT_ERROR, "Particle sensor initialisation failed");
    
    sample_noise_sensor();
    sample_particle_sensor();
    
    if (!sleep_particle_sensor()) error_handler(-1, true, PS_SLEEP_ERROR, "Failed to put the particle sensor to sleep");

    boot_count++;
    
    encode_payload(&payload, &ps_result, &ns_result);
    buffering_counter++;    // Amount of batched readings within the payload
    
    bool send_payload = !(buffering_counter < BUFFERING_THRESHOLD);
    if (send_payload) {
        random_tx_delay(MAX_TX_DELAY_S);

        DEBUG_PRINTLN("[TRANSMIT] Transmitting payload");
        transmit_payload(&payload);

        buffering_counter = 0;
        memset(&payload, 0, sizeof(payload_t));
    }

    radio.sleep();

    uint32_t sleep_time_ms = calculate_sleep_time();
    DEBUG_PRINT("[END]      Entering sleep for: "); DEBUG_PRINT(sleep_time_ms); DEBUG_PRINTLN(" ms");
    
    esp_sleep_enable_timer_wakeup(sleep_time_ms);
    esp_deep_sleep_start();
}

void loop() {
    // keep empty
}