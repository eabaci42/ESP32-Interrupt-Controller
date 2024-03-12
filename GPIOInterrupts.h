#ifndef GPIO_INTERRUPTS_H
#define GPIO_INTERRUPTS_H

#include <functional>
#include <map>

// ESP32 için GPIO kesme modları
enum class GPIOInterruptMode {
    RISING_EDGE,    // Yükselen kenar tetiklemesi
    FALLING_EDGE,   // Düşen kenar tetiklemesi
    BOTH_EDGES,     // Her iki kenar tetiklemesi
    LOW_LEVEL,      // Düşük seviye tetiklemesi
    HIGH_LEVEL      // Yüksek seviye tetiklemesi
};

// GPIO pinleri için kesme hizmet rutini (ISR) tür tanımı
using GPIOSInterruptHandler = std::function<void(void)>;

class GPIOInterruptsController {
public:
    // GPIO pinini belirtilen modda kesme için kaydetme
    static void register_interrupt(int pin, GPIOInterruptMode mode, GPIOSInterruptHandler handler);

    // GPIO pinindeki kesme kaydını kaldırma
    static void unregister_interrupt(int pin);

    // Tüm kesme kayıtlarını kaldırma
    static void clear_interrupts();

private:
    // Pin numarasına göre kesme hizmet rutinlerini saklayan bir harita
    static std::map<int, GPIOSInterruptHandler> handlers;

    // ESP32 donanım kesmesi yöneticisi tarafından çağrılacak iç kesme işleyici
    static void internal_interrupt_handler(int pin);

    // GPIO pinlerini ve modlarını donanımsal olarak yapılandırma
    static void configure_pin(int pin, GPIOInterruptMode mode);

    // Yapılandırılmış pinleri ve modları saklamak için kullanılır
    static std::map<int, GPIOInterruptMode> configured_pins;
};

#endif // GPIO_INTERRUPTS_H
