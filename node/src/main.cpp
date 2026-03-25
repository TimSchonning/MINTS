#include <Seeed_HM330X.h>

HM330X sensor;
uint8_t sensor_buf[30];

/* 
1. ta data
2. kalk. snitt baserat på tid och antal
3. skicka
*/



/*Heats up for 30s*/
void setup() {
    SERIAL_OUTPUT.begin(115200);
    delay(100);
    SERIAL_OUTPUT.println("Serial start");
    if (sensor.init()) {
        SERIAL_OUTPUT.println("HM330X init failed!!");
        while (1);
    }

}


void loop() {
    if (sensor.read_sensor_value(sensor_buf, 29)) {
        SERIAL_OUTPUT.println("HM330X read result failed!!");
    }
    parse_result_value(sensor_buf);
    parse_result(sensor_buf);
    SERIAL_OUTPUT.println("");
    delay(5000);
}