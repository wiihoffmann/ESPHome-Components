#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/log.h"

#include "../SumpPumpController.h"

namespace esphome {
namespace sump_pump_controller {

class BatteryChargerSwitch : public switch_::Switch, public Parented<SumpPumpController>{
  public:
    BatteryChargerSwitch(){};
    void write_state(bool state) override;
};

} //namespace enable_switch
} //namespace esphome