#include "GPIOInterrupts.h"
#include <Arduino.h> // ESP32 geliştirme için Arduino framework'ünü kullanıyoruz.

// Static değişkenlerin başlangıç değerlerini ayarlama
std::map<int, GPIOSInterruptHandler> GPIOInterruptsController::handlers;
std::map<int, GPIOInterruptMode> GPIOInterruptsController::configured_pins;

void GPIOInterruptsController::register_interrupt(int pin, GPIOInterruptMode mode, GPIOSInterruptHandler handler) {
    // Pin modunu ve kesme hizmet rutinini kaydet
    handlers[pin] = handler;
    configured_pins[pin] = mode;

    // Pin yapılandırmasını donanımsal olarak ayarla
    configure_pin(pin, mode);
}

void GPIOInterruptsController::unregister_interrupt(int pin) {
    // Kesme hizmet rutini ve pin yapılandırmasını kaldır
    handlers.erase(pin);
    configured_pins.erase(pin);

    // Pin'i kesme olmayacak şekilde yapılandır
    pinMode(pin, INPUT);
}

void GPIOInterruptsController::clear_interrupts() {
    // Tüm kesmeleri kaldır ve pin yapılandırmalarını sıfırla
    handlers.clear();
    configured_pins.clear();
}

void GPIOInterruptsController::configure_pin(int pin, GPIOInterruptMode mode) {
    // Pin modunu ve kesme türünü ESP32 donanımına kaydet
    pinMode(pin, INPUT);
    int interruptMode = convertMode(mode);
    attachInterrupt(pin, std::bind(&GPIOInterruptsController::internal_interrupt_handler, pin), interruptMode);
}

void GPIOInterruptsController::internal_interrupt_handler(int pin) {
    // Kaydedilen kesme hizmet rutinini çağır
    if (handlers.find(pin) != handlers.end()) {
        handlers[pin](); // Hizmet rutinini çağır
    }
}

int GPIOInterruptsController::convertMode(GPIOInterruptMode mode) {
    // ESP32 için kesme modunu Arduino moduna dönüştür
    switch (mode) {
        case GPIOInterruptMode::RISING_EDGE:
            return RISING;
        case GPIOInterruptMode::FALLING_EDGE:
            return FALLING;
        case GPIOInterruptMode::BOTH_EDGES:
            return CHANGE;
        case GPIOInterruptMode::LOW_LEVEL:
            return LOW;
        case GPIOInterruptMode::HIGH_LEVEL:
            return HIGH;
        default:
            return -1; // Geçersiz mod
    }
}
