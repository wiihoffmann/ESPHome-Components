#include "PumpSwitch.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Pump Override Switch";

void PumpSwitch::write_state(bool state) {
    this->parent_->updateChargerState(false);
    this->parent_->updatePumpState(state);
}

} //namespace sump_pump_controller
} //namespace esphome