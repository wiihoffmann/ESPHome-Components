
#include "SumpPumpController.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Sump Pump Controller";

void SumpPumpController::setup() {
    return;
}

void SumpPumpController::loop() {
    if(App.get_loop_component_start_time() >= time+1000){
        time = App.get_loop_component_start_time();
        ESP_LOGD(TAG, "Dumping enable switch state: %i", enableSW->state);
    }
    
}

void SumpPumpController::dump_config(){
    if(enableSW==nullptr) ESP_LOGD(TAG, "Enable switch is null!");
    else ESP_LOGD(TAG, "Enable switch is set!");

    if(pumpSW==nullptr) ESP_LOGD(TAG, "Pump switch is null!");
    else ESP_LOGD(TAG, "Pump switch is set!");

    if(batteryChargerSW==nullptr) ESP_LOGD(TAG, "Battery Charger switch is null!");
    else ESP_LOGD(TAG, "Battery charger switch is set!");
}

} //namespace sump_pump_controller
} //namespace esphome