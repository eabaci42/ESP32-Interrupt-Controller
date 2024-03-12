class IInterruptController {
public:
    // Kesme kaynağını kaydet
    virtual void register_interrupt(int interrupt_pin, void (*callback)(void), int mode) = 0;
    
    // Kesme kaydını kaldır
    virtual void unregister_interrupt(int interrupt_pin) = 0;
    
    // Kesme yöneticisi, kesme gerçekleştiğinde çağrılacak
    virtual void interrupt_handler() = 0;
    
    // Yıkıcı
    virtual ~IInterruptController() {}
};
