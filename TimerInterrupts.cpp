#include "TimerInterrupts.h"
#include <Arduino.h>

std::map<unsigned int, TimerInterruptsController::TimerInfo> TimerInterruptsController::timers;

void TimerInterruptsController::set_timer(unsigned int timer_id, unsigned long interval, TimerInterruptHandler handler, bool repeat) {
    // Zamanlayıcı bilgisini ayarla veya güncelle
    timers[timer_id] = {interval, millis(), handler, repeat};
}

void TimerInterruptsController::clear_timer(unsigned int timer_id) {
    // Belirtilen ID'ye sahip zamanlayıcıyı kaldır
    timers.erase(timer_id);
}

void TimerInterruptsController::clear_all_timers() {
    // Tüm zamanlayıcıları kaldır
    timers.clear();
}

void TimerInterruptsController::check_timers() {
    unsigned long current_time = millis();
    for (auto it = timers.begin(); it != timers.end(); ) {
        auto& timer_id = it->first;
        auto& timer = it->second;
        if (current_time - timer.last_trigger >= timer.interval) {
            // Zamanlayıcı süresi doldu, handler'ı çağır
            timer.handler();
            // Son tetiklenme zamanını güncelle
            timer.last_trigger = current_time;
            if (timer.repeat) {
                ++it; // Tekrar eden zamanlayıcılar için iteratörü güncelle
            } else {
                // Tekrar etmeyen zamanlayıcıyı kaldır
                it = timers.erase(it);
            }
        } else {
            ++it; // Zamanlayıcı tetiklenmedi, iteratörü güncelle
        }
    }
}
