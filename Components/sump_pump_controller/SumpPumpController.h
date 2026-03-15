#pragma once

#include "esphome/core/application.h"
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/log.h"
// #include "switch/enable_switch.h"

namespace esphome {
namespace sump_pump_controller {

class SumpPumpController : public Component {
  public:
    void setEnableSwitch(switch_::Switch *sw){enableSW = sw;}
    void setPumpSwitch(switch_::Switch *sw){pumpSW = sw;}
    void setBatteryChargerSwitch(switch_::Switch *sw){batteryChargerSW = sw;}

    void setup() override;
    void loop() override;
    void dump_config() override;
    
  private:
    switch_::Switch *enableSW{nullptr};
    switch_::Switch *pumpSW{nullptr};
    switch_::Switch *batteryChargerSW{nullptr};
    uint32_t time;
};


}  // namespace sump_pump_controller
}  // namespace esphome