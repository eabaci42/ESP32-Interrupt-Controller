#ifndef TOUCH_SENSOR_INTERRUPTS_H
#define TOUCH_SENSOR_INTERRUPTS_H

#include <functional>
#include <map>

// Dokunmatik sensör kesmeleri için callback fonksiyon türü
using TouchInterruptHandler = std::function<void()>;

class TouchSensorInterruptsController {
public:
    // Dokunmatik sensörü belirli bir hassasiyet seviyesi ile kesme oluşturacak şekilde ayarla
    static void set_touch_interrupt(int sensor_pin, int threshold, TouchInterruptHandler handler);

    // Dokunmatik sensör kesme kaydını kaldır
    static void clear_touch_interrupt(int sensor_pin);

    // Tüm dokunmatik sensör kesme kayıtlarını kaldır
    static void clear_all_touch_interrupts();

private:
    // Dokunmatik sensör bilgisini tutan iç yapı
    struct TouchSensorInfo {
        int threshold;
        TouchInterruptHandler handler;
    };

    // Dokunmatik sensör bilgilerini saklayan bir map
    static std::map<int, TouchSensorInfo> sensors;

    // Dokunmatik sensörleri kontrol etmek ve gerektiğinde kesmeleri tetiklemek için kullanılan iç metod
    static void check_sensors();
};

#endif // TOUCH_SENSOR_INTERRUPTS_H
