
#include "SumpPumpController.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Sump Pump Controller";


void SumpPumpController::onSumpLevelUpdate(float level){
    sumpLevelm = sumpDepthm - level;
    if(!std::isnan(sumpLevelm) && sumpLevelm >= sumpHighLimitm) levelConfidence++;
    else levelConfidence = 0;
}


void SumpPumpController::onInternalVoltageSensorUpdate(float voltage){
    if(voltage <= chargerCutIn) voltageConfidence++;
    else voltageConfidence = 0;
}


void SumpPumpController::updatePumpState(bool state){
    if(state) PumpFET->turn_on();
    else PumpFET->turn_off();

    if(PumpSW != nullptr) PumpSW->publish_state(state);
    pumpOn = state;
}


void SumpPumpController::updateChargerState(bool state){
    if(state) ChargeFET->turn_on();
    else ChargeFET->turn_off();

    if(BatteryChargerSW != nullptr) BatteryChargerSW->publish_state(state);
    charging = state;
}


void SumpPumpController::updateManualModeState(bool state){
    bool oldState = manualMode;
    
    if(state) manualMode = true;
    if(!state && !PhysicalManualSwitch->state) manualMode = false;

    if(EnableSW != nullptr) EnableSW->publish_state(manualMode);
    
    // turn off the pump and charger when entering manual mode
    if(oldState != manualMode && manualMode){
        updatePumpState(false);
        updateChargerState(false);
    }
}


void SumpPumpController::updateDashboard(){
    if(DashboardLevelSensor != nullptr){
        DashboardLevelSensor->publish_state(sumpLevelm * 100.0f);
    }

    if(DashboardVoltageSensor != nullptr){
        DashboardVoltageSensor->publish_state(InternalVoltageSensor->state);
    }

    if(DashboardCurrentSensor != nullptr){
        DashboardCurrentSensor->publish_state(InternalCurrentSensor->state);     
    }
}


void SumpPumpController::updateLEDs(){
    if     (!manualMode && !charging && !pumpOn) ledState = ledStates::SOLID_GREEN;
    else if(!manualMode && !charging &&  pumpOn) ledState = ledStates::SOLID_GREEN_FLASH_RED;
    else if(!manualMode &&  charging && !pumpOn) ledState = ledStates::SOLID_RED_GREEN;
    else if(!manualMode &&  charging &&  pumpOn) ledState = ledStates::RED_GREEN_ALTERNATE;
    else if( manualMode && !charging && !pumpOn) ledState = ledStates::FLASH_GREEN;
    else if( manualMode && !charging &&  pumpOn) ledState = ledStates::FLASH_RED_GREEN;
    else if( manualMode &&  charging && !pumpOn) ledState = ledStates::FLASH_GREEN_SOLID_RED;
    else if( manualMode &&  charging &&  pumpOn) ledState = ledStates::RED_GREEN_ALTERNATE;

    switch (ledState){
        case ledStates::SOLID_GREEN:
            greenLEDstate = true;
            redLEDstate = false;
            break;
        case ledStates::FLASH_GREEN:
            greenLEDstate = !greenLEDstate;
            redLEDstate = false;
            break;
        case ledStates::SOLID_RED_GREEN:
            greenLEDstate = true;
            redLEDstate = true;
            break;
        case ledStates::FLASH_RED_GREEN:
            greenLEDstate = !greenLEDstate;
            redLEDstate = greenLEDstate;
            break;
        case ledStates::SOLID_GREEN_FLASH_RED:
            greenLEDstate = true;
            redLEDstate = !redLEDstate;
            break;
        case ledStates::FLASH_GREEN_SOLID_RED:
            greenLEDstate = !greenLEDstate;
            redLEDstate = true;
            break;
        case ledStates::RED_GREEN_ALTERNATE:
            greenLEDstate = !greenLEDstate;
            redLEDstate = !greenLEDstate;
            break;
    }

    if(greenLEDstate) GreenLED->turn_on();
    else GreenLED->turn_off();
    if(redLEDstate) RedLED->turn_on();
    else RedLED->turn_off();
}


void SumpPumpController::setup() {
    SumpLevelSensor->add_on_state_callback([this](float x){onSumpLevelUpdate(x);});
    InternalVoltageSensor->add_on_state_callback([this](float x){onInternalVoltageSensorUpdate(x);});
    PhysicalManualSwitch->add_on_state_callback([this](bool state){updateManualModeState(state);});
}


void SumpPumpController::loop() {
    // Set the manual switch state in the dashboard on first loop.
    // This cannot be done in setup() as the switch may not be initialized yet.
    if(!initialManualStateSet){
        manualMode = PhysicalManualSwitch->state;
        if(EnableSW != nullptr) EnableSW->publish_state(manualMode);
        initialManualStateSet = true;
    }

    // Publish new states to HomeAssistant every publishRate seconds
    if(App.get_loop_component_start_time() >= lastPublishTime + (publishRate*1000)){
        updateDashboard();
        lastPublishTime = App.get_loop_component_start_time();
    }

    // Process LED states at the LED flash rate
    if(App.get_loop_component_start_time() >= ledTimer + ledFlashRatems){
        updateLEDs();
        ledTimer = App.get_loop_component_start_time();
    }

    if(!manualMode){
        // Battery charger turn-on. Cannot charge and pump!
        if(!charging && !pumpOn && (voltageConfidence >= measurementConfidenceThreshold)){
            updateChargerState(true);
            voltageConfidence = 0;
            chargeStartTime = App.get_loop_component_start_time();
        }
        // Battery charger turn-off
        else if((InternalVoltageSensor->state >= chargerCutOut) || (App.get_loop_component_start_time() >= chargeStartTime + (maxChargeTime*1000))){
            updateChargerState(false);
        }

        // Pump turn-on. Cannot charge and pump!
        if(!pumpOn && (levelConfidence >= measurementConfidenceThreshold)){
            updateChargerState(false);
            updatePumpState(true);
            levelConfidence = 0;
        }
        // Pump turn-off
        else if(pumpOn && sumpLevelm <= sumpLowLimitm){
            updatePumpState(false);
        }
    }
}


// This prints on device startup
void SumpPumpController::dump_config(){
    if(DashboardLevelSensor==nullptr) ESP_LOGCONFIG(TAG, "Sump level will NOT be reported!");
    else ESP_LOGCONFIG(TAG, "Sump level will be reported!");

    if(DashboardVoltageSensor==nullptr) ESP_LOGCONFIG(TAG, "Battery voltage will NOT be reported!");
    else ESP_LOGCONFIG(TAG, "Battery voltage will be reported!");

    if(DashboardCurrentSensor==nullptr) ESP_LOGCONFIG(TAG, "Battery current will NOT be reported!");
    else ESP_LOGCONFIG(TAG, "Battery current will be reported!");

    ESP_LOGCONFIG(TAG, "Sump Depth is %.3f m", sumpDepthm);
    ESP_LOGCONFIG(TAG, "Sump High Limit is %.3f m", sumpHighLimitm);
    ESP_LOGCONFIG(TAG, "Sump Low Limit is %.3f m", sumpLowLimitm);
    ESP_LOGCONFIG(TAG, "Charger cut-in voltage is %.3fv", chargerCutIn);
    ESP_LOGCONFIG(TAG, "Charger cut-out voltage is %.3fv", chargerCutOut);
    ESP_LOGCONFIG(TAG, "Maximum charge duration is %.3fs", maxChargeTime);
    ESP_LOGCONFIG(TAG, "Measurement confidence threshold is %.3fs", maxChargeTime);
    ESP_LOGCONFIG(TAG, "HomeAssistant dashboard will update every %.1fs", publishRate);
}

} //namespace sump_pump_controller
} //namespace esphome