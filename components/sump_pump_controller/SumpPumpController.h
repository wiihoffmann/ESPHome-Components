#pragma once

#include "esphome/core/application.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/ultrasonic/ultrasonic_sensor.h"
#include "esphome/components/gpio/output/gpio_binary_output.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/sensor/sensor.h"

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
    void setPublishRate(float x){publishRate = x;}
    void setMeasurementConfidence(uint8_t x){measurementConfidenceThreshold = x;}

    void setEnableSwitch(switch_::Switch *sw){EnableSW = sw;}
    void setPumpSwitch(switch_::Switch *sw){PumpSW = sw;}
    void setBatteryChargerSwitch(switch_::Switch *sw){BatteryChargerSW = sw;}

    void setRedLEDPin(gpio::GPIOBinaryOutput *pin){RedLED = pin;}
    void setGreenLEDPin(gpio::GPIOBinaryOutput *pin){GreenLED = pin;}
    void setChargeFETPin(gpio::GPIOBinaryOutput *pin){ChargeFET = pin;}
    void setPumpFETPin(gpio::GPIOBinaryOutput *pin){PumpFET = pin;}
    
    void setDashboardCurrentSensor(sensor::Sensor *sens){DashboardCurrentSensor = sens;}
    void setDashboardVoltageSensor(sensor::Sensor *sens){DashboardVoltageSensor = sens;}
    void setDashboardLevelSensor(sensor::Sensor *sens){DashboardLevelSensor = sens;}
    void setInternalCurrentSensor(sensor::Sensor *sens){InternalCurrentSensor = sens;}
    void setInternalVoltageSensor(sensor::Sensor *sens){InternalVoltageSensor = sens;}
    void setWaterLevelSensor(sensor::Sensor *sens){InternalVoltageSensor = sens;}
    
    void setManualSwitchPin(binary_sensor::BinarySensor *pin){PhysicalManualSwitch = pin;}
    
    void setDistanceSensor(ultrasonic::UltrasonicSensorComponent *sens){SumpLevelSensor = sens;}

    void setup() override;
    void loop() override;
    void dump_config() override;
    void updatePumpState(bool state);
    void updateChargerState(bool state);
    void updateManualModeState(bool state);

    
  private:
    const uint16_t ledFlashRatems = 500;

    enum ledStates{
      SOLID_GREEN,
      FLASH_GREEN,
      SOLID_RED_GREEN,
      FLASH_RED_GREEN,
      SOLID_GREEN_FLASH_RED,
      FLASH_GREEN_SOLID_RED,
      RED_GREEN_ALTERNATE,
    };

    // Set by YAML device config.
    switch_::Switch *EnableSW{nullptr};
    switch_::Switch *PumpSW{nullptr};
    switch_::Switch *BatteryChargerSW{nullptr};
    esphome::gpio::GPIOBinaryOutput *RedLED{nullptr};
    esphome::gpio::GPIOBinaryOutput *GreenLED{nullptr};
    esphome::gpio::GPIOBinaryOutput *ChargeFET{nullptr};
    esphome::gpio::GPIOBinaryOutput *PumpFET{nullptr};
    sensor::Sensor *DashboardVoltageSensor{nullptr};
    sensor::Sensor *DashboardCurrentSensor{nullptr};
    sensor::Sensor *DashboardLevelSensor{nullptr};
    sensor::Sensor *InternalVoltageSensor{nullptr};
    sensor::Sensor *InternalCurrentSensor{nullptr};
    binary_sensor::BinarySensor *PhysicalManualSwitch{nullptr};
    ultrasonic::UltrasonicSensorComponent *SumpLevelSensor{nullptr};
    
    // Set by YAML device config. Treat as constant!
    float sumpDepthm = 0;
    float sumpHighLimitm = 0;
    float sumpLowLimitm = 0;
    volatile float sumpLevelm = 0;
    float chargerCutIn = 0;
    float chargerCutOut = 0;
    float maxChargeTime = 0;
    float publishRate = 0;
    uint8_t measurementConfidenceThreshold = 0;

    // Working set variables
    uint32_t lastPublishTime = 0;
    uint32_t ledTimer = 0;
    ledStates ledState = ledStates::SOLID_GREEN;
    uint32_t chargeStartTime = 0;
    bool redLEDstate = false;
    bool greenLEDstate = false;
    bool initialManualStateSet = false;
    volatile bool charging = false;
    volatile bool pumpOn = false;
    volatile bool manualMode = false;
    volatile uint8_t voltageConfidence = 0;
    volatile uint8_t levelConfidence = 0;

    void onSumpLevelUpdate(float level);
    void onInternalVoltageSensorUpdate(float voltage);
    void onInternalCurrentSensorUpdate(float current);
    void updateDashboard();
    void updateLEDs();
};


}  // namespace sump_pump_controller
}  // namespace esphome