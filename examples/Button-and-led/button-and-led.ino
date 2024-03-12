#include "GPIOInterrupts.h" // Önceden oluşturduğumuz kütüphaneyi include ediyoruz

const int buttonPin = 0; // Buton için GPIO pin numarası
const int ledPin = 2;    // LED için GPIO pin numarası
volatile bool ledState = false; // LED'in mevcut durumunu tutacak değişken


void IRAM_ATTR handleButtonPress() {
    ledState = !ledState; // LED durumunu değiştir
    digitalWrite(ledPin, ledState); // LED'in GPIO pinine yeni durumu yaz
}


void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT); // LED pinini çıkış olarak ayarla
    pinMode(buttonPin, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve iç pull-up direncini etkinleştir

    // Butona basıldığında handleButtonPress fonksiyonunu çağıracak şekilde kesme ayarla
    GPIOInterruptsController::register_interrupt(buttonPin, GPIOInterruptMode::FALLING_EDGE, handleButtonPress);
}

void loop() {
    // Burada yapılacak bir şey yok, her şey kesme tarafından yönetiliyor
}
