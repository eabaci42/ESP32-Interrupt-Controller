#ifndef PERIPHERAL_INTERRUPTS_H
#define PERIPHERAL_INTERRUPTS_H

#include <functional>
#include <map>

// Peripheral olayları için callback fonksiyon türü
using PeripheralEventHandler = std::function<void(int)>;

enum class PeripheralEvent {
    DATA_RECEIVED,    // Veri alındığında
    TRANSMIT_COMPLETE, // Veri iletimi tamamlandığında
    ERROR_OCCURED     // Hata oluştuğunda
};

class PeripheralInterruptsController {
public:
    // Peripheral olayını dinlemek için handler'ı kaydet
    static void register_event_handler(int peripheral_id, PeripheralEvent event, PeripheralEventHandler handler);

    // Belirli bir peripheral için tüm olay handler'larını kaldır
    static void clear_handlers(int peripheral_id);

    // Tüm peripheral olay handler'larını kaldır
    static void clear_all_handlers();

private:
    // Peripheral ID ve olay türüne göre handler'ları saklayan karmaşık bir yapı
    static std::map<std::pair<int, PeripheralEvent>, PeripheralEventHandler> handlers;

    // Peripheral olaylarını dinlemek ve yönlendirmek için iç metodlar
    static void on_data_received(int peripheral_id);
    static void on_transmit_complete(int peripheral_id);
    static void on_error_occured(int peripheral_id);
};

#endif // PERIPHERAL_INTERRUPTS_H
