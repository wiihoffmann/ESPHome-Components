
#include "SumpPumpController.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Sump Pump Controller";

bool state = false;
uint32_t time;

void SumpPumpController::onSumpLevelUpdate(float value){
    DashboardVoltageSensor->publish_state(value);
    ESP_LOGCONFIG(TAG, "🚨🚨🚨in callback!🚨🚨🚨");
}

void SumpPumpController::setup() {
    sumpLevelSensor->add_on_raw_state_callback([this](float x){onSumpLevelUpdate(x);});
    //sumpLevelSensor->add_on_state_callback([this](float x){ESP_LOGCONFIG(TAG, "🚨🚨🚨The other one!🚨🚨🚨");});
}

void SumpPumpController::loop() {
    if(App.get_loop_component_start_time() >= time+1000){
        time = App.get_loop_component_start_time();
        RedLED->set_state((state = !state));
        GreenLED->set_state(!state);
        //DashboardVoltageSensor->publish_state(12.0);
    }
    
}

void SumpPumpController::dump_config(){
    if(enableSW==nullptr) ESP_LOGCONFIG(TAG, "Enable switch is NOT present!");
    else ESP_LOGCONFIG(TAG, "Enable switch is set!");

    if(pumpSW==nullptr) ESP_LOGCONFIG(TAG, "Pump switch is NOT present!");
    else ESP_LOGCONFIG(TAG, "Pump switch is set!");

    if(batteryChargerSW==nullptr) ESP_LOGCONFIG(TAG, "Battery Charger switch is NOT present!");
    else ESP_LOGCONFIG(TAG, "Battery charger switch is set!");

    ESP_LOGCONFIG(TAG, "Sump Depth is %.3f m", sumpDepthm);
    ESP_LOGCONFIG(TAG, "Sump High Limit is %.3f m", sumpHighLimitm);
    ESP_LOGCONFIG(TAG, "Sump Low Limit is %.3f m", sumpLowLimitm);
    ESP_LOGCONFIG(TAG, "Charger cut-in voltage is %.3fv", chargerCutIn);
    ESP_LOGCONFIG(TAG, "Charger cut-out voltage is %.3fv", chargerCutOut);
    ESP_LOGCONFIG(TAG, "Maximum charge duration is %.3fs", maxChargeTime);
}

} //namespace sump_pump_controller
} //namespace esphome