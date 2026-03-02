#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "enable_switch.h"

namespace esphome {
namespace sump_pump_controller {

class sump_pump_controller : public Component {
  public:
    //void set_enable_switch(switch_::Switch *sw){enableSW = sw;}

    void setup() override;
    void loop() override;
    void dump_config() override;
  private:
    enable_switch::EnableSwitch *enableSW;
};


}  // namespace sump_pump_controller
}  // namespace esphome