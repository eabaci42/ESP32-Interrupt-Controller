#ifndef NETWORK_INTERRUPTS_H
#define NETWORK_INTERRUPTS_H

#include <WiFi.h>
#include <functional>
#include <vector>

// Ağ durum değişikliği için callback fonksiyon türü
using NetworkStatusChangedHandler = std::function<void(WiFiEvent_t event, WiFiEventInfo_t info)>;

class NetworkInterruptsController {
public:
    // Ağ durum değişikliği olaylarını dinlemek için handler'ı kaydet
    static void register_network_status_changed_handler(NetworkStatusChangedHandler handler);

    // Tüm ağ durum değişikliği handler'larını kaldır
    static void clear_handlers();

    // Ağ durumu değişikliklerini ve gelen veri paketlerini kontrol et (Bu fonksiyon, main loop'ta düzenli olarak çağrılmalıdır.)
    static void check_network_events();

private:
    // Ağ durum değişikliği handler'larını saklayan vektör
    static std::vector<NetworkStatusChangedHandler> handlers;

    // WiFi olayları için iç callback fonksiyonu
    static void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
};

#endif // NETWORK_INTERRUPTS_H
