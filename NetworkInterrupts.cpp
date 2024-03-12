#include "NetworkInterrupts.h"

std::vector<NetworkStatusChangedHandler> NetworkInterruptsController::handlers;

void NetworkInterruptsController::register_network_status_changed_handler(NetworkStatusChangedHandler handler) {
    handlers.push_back(handler);
    // WiFi olayları için ilk handler kaydedildiğinde, WiFi olayları dinlenmeye başlar
    if (handlers.size() == 1) {
        WiFi.onEvent(onWiFiEvent);
    }
}

void NetworkInterruptsController::clear_handlers() {
    handlers.clear();
    // Tüm handler'lar kaldırıldığında, WiFi olayları dinlemeyi durdur
    WiFi.removeEvent(onWiFiEvent);
}

void NetworkInterruptsController::check_network_events() {
    // Bu fonksiyon özellikle gelen veri paketlerini kontrol etmek için kullanılabilir.
    // Ancak ESP32, WiFi olaylarını zaten asenkron olarak işlediğinden, bu fonksiyonun
    // ağ olayları için ek bir işlevi olmayabilir.
}

void NetworkInterruptsController::onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    for (auto& handler : handlers) {
        handler(event, info);
    }
}

