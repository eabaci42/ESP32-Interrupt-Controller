#include "TouchSensorInterrupts.h"
#include <Arduino.h>

std::map<int, TouchSensorInterruptsController::TouchSensorInfo> TouchSensorInterruptsController::sensors;

void TouchSensorInterruptsController::set_touch_interrupt(int sensor_pin, int threshold, TouchInterruptHandler handler) {
    // Sensör bilgisini ayarla veya güncelle
    sensors[sensor_pin] = {threshold, handler};
    // Sensör pinini yapılandır (ESP32 spesifik fonksiyonlarını kullanarak)
}

void TouchSensorInterruptsController::clear_touch_interrupt(int sensor_pin) {
    // Belirtilen PIN'le ilişkili dokunmatik sensörü kaldır
    sensors.erase(sensor_pin);
    // Gerekirse, sensör pinini pasifize et (ESP32 spesifik fonksiyonlarını kullanarak)
}

void TouchSensorInterruptsController::clear_all_touch_interrupts() {
    // Tüm dokunmatik sensörleri kaldır
    sensors.clear();
    // Gerekirse, tüm sensör pinlerini pasifize et (ESP32 spesifik fonksiyonlarını kullanarak)
}

void TouchSensorInterruptsController::check_sensors() {
    // Her sensör için dokunma durumunu kontrol et ve gerekirse handler'ı tetikle
    for (const auto& pair : sensors) {
        int sensor_value = touchRead(pair.first); // ESP32 spesifik fonksiyon
        if (sensor_value < pair.second.threshold) {
            // Dokunma algılandı, handler'ı çağır
            pair.second.handler();
        }
    }
}
