#include "PeripheralInterrupts.h"

std::map<std::pair<int, PeripheralEvent>, PeripheralEventHandler> PeripheralInterruptsController::handlers;

void PeripheralInterruptsController::register_event_handler(int peripheral_id, PeripheralEvent event, PeripheralEventHandler handler) {
    handlers[{peripheral_id, event}] = handler;
}

void PeripheralInterruptsController::clear_handlers(int peripheral_id) {
    for(auto it = handlers.begin(); it != handlers.end(); ) {
        if(it->first.first == peripheral_id) {
            it = handlers.erase(it);
        } else {
            ++it;
        }
    }
}

void PeripheralInterruptsController::clear_all_handlers() {
    handlers.clear();
}

void PeripheralInterruptsController::on_data_received(int peripheral_id) {
    auto handler_it = handlers.find({peripheral_id, PeripheralEvent::DATA_RECEIVED});
    if(handler_it != handlers.end()) {
        handler_it->second(peripheral_id);
    }
}

void PeripheralInterruptsController::on_transmit_complete(int peripheral_id) {
    auto handler_it = handlers.find({peripheral_id, PeripheralEvent::TRANSMIT_COMPLETE});
    if(handler_it != handlers.end()) {
        handler_it->second(peripheral_id);
    }
}

void PeripheralInterruptsController::on_error_occured(int peripheral_id) {
    auto handler_it = handlers.find({peripheral_id, PeripheralEvent::ERROR_OCCURED});
    if(handler_it != handlers.end()) {
        handler_it->second(peripheral_id);
    }
}
