#pragma once

#include "esphome/core/application.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/ultrasonic/ultrasonic_sensor.h"
#include "esphome/components/gpio/output/gpio_binary_output.h"
// #include "esphome/components/gpio/switch/gpio_switch.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/sensor/sensor.h"
// #include "switch/enable_switch.h"

namespace esphome {
namespace sump_pump_controller {

class SumpPumpController : public Component {
  public:
    void setSumpDepthm(float x){sumpDepthm = x;}
    void setHighLimitm(float x){sumpHighLimitm = x;}
    void setLowLimitm(float x){sumpLowLimitm = x;}
    void setChargerCutIn(float x){chargerCutIn = x;}
    void setChargerCutOut(float x){chargerCutOut = x;}
    void setMaxChargeTime(float x){maxChargeTime = x;}  
  
    void setEnableSwitch(switch_::Switch *sw){enableSW = sw;}
    void setPumpSwitch(switch_::Switch *sw){pumpSW = sw;}
    void setBatteryChargerSwitch(switch_::Switch *sw){batteryChargerSW = sw;}

    void setRedLEDPin(gpio::GPIOBinaryOutput *pin){RedLED = pin;}
    void setGreenLEDPin(gpio::GPIOBinaryOutput *pin){GreenLED = pin;}
    void setChargeFETPin(gpio::GPIOBinaryOutput *pin){ChargeFET = pin;}
    void setPumpFETPin(gpio::GPIOBinaryOutput *pin){PumpFET = pin;}
    
    void setManualSwitchPin(binary_sensor::BinarySensor *pin){ManualSwitch = pin;}
    
    void setSumpLevelSensor(ultrasonic::UltrasonicSensorComponent *sens){sumpLevelSensor = sens;}

    void setup() override;
    void loop() override;
    void dump_config() override;
    
  private:
    switch_::Switch *enableSW{nullptr};
    switch_::Switch *pumpSW{nullptr};
    switch_::Switch *batteryChargerSW{nullptr};
    
    esphome::gpio::GPIOBinaryOutput *RedLED{nullptr};
    esphome::gpio::GPIOBinaryOutput *GreenLED{nullptr};
    esphome::gpio::GPIOBinaryOutput *ChargeFET{nullptr};
    esphome::gpio::GPIOBinaryOutput *PumpFET{nullptr};
    
    binary_sensor::BinarySensor *ManualSwitch{nullptr};
    
    ultrasonic::UltrasonicSensorComponent *sumpLevelSensor{nullptr};

    float sumpDepthm = 0;
    float sumpHighLimitm = 0;
    float sumpLowLimitm = 0;
    float chargerCutIn = 0;
    float chargerCutOut = 0;
    float maxChargeTime = 0;
};


}  // namespace sump_pump_controller
}  // namespace esphome