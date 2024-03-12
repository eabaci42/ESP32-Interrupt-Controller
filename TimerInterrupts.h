#ifndef TIMER_INTERRUPTS_H
#define TIMER_INTERRUPTS_H

#include <functional>
#include <map>

// Timer kesmeleri için callback fonksiyon türü
using TimerInterruptHandler = std::function<void(void)>;

class TimerInterruptsController {
public:
    // Zamanlayıcıyı belirli bir süre sonra kesme oluşturacak şekilde ayarla ve tekrar edip etmeyeceğini belirt
    static void set_timer(unsigned int timer_id, unsigned long interval, TimerInterruptHandler handler, bool repeat = false);

    // Zamanlayıcı kesme kaydını kaldır
    static void clear_timer(unsigned int timer_id);

    // Tüm zamanlayıcı kesme kayıtlarını kaldır
    static void clear_all_timers();

    // Zamanlayıcıları kontrol et ve gerekirse kesmeleri tetikle (Bu fonksiyon, main loop'ta düzenli olarak çağrılmalıdır.)
    static void check_timers();

private:
    // Zamanlayıcı bilgisini tutan iç yapı
    struct TimerInfo {
        unsigned long interval;
        unsigned long last_trigger;
        TimerInterruptHandler handler;
        bool repeat;
    };

    // Zamanlayıcı bilgilerini saklayan bir map
    static std::map<unsigned int, TimerInfo> timers;
};

#endif // TIMER_INTERRUPTS_H
