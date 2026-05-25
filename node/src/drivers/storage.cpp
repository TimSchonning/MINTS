#include "master.h"

Preferences prefs;

static void write_nvs(const char* key, uint8_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putUChar(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void write_nvs(const char* key, uint16_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putUShort(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void write_nvs(const char* key, uint32_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putULong(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void read_nvs(const char* key, uint8_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getUChar(key, 0);
    prefs.end();
}

static void read_nvs(const char* key, uint16_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getUShort(key, 0);
    prefs.end();
}

static void read_nvs(const char* key, uint32_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getULong(key, 0);
    prefs.end();
}

void add_to_nvs(uint8_t boot_count, uint8_t pm1, uint8_t pm25, uint16_t noise) {
    char key[16];
    
    snprintf(key, sizeof(key), "i_%u_p1", boot_count);
    write_nvs(key, pm1);
    
    snprintf(key, sizeof(key), "i_%u_p2", boot_count);
    write_nvs(key, pm25);
    
    snprintf(key, sizeof(key), "i_%u_n", boot_count);
    write_nvs(key, noise);
}
