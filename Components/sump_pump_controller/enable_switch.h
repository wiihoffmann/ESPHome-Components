#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace enable_switch {

class EnableSwitch : public switch_::Switch{
 public:
  EnableSwitch(){};
  void write_state(bool state) override;
};

} //namespace enable_switch
} //namespace esphome