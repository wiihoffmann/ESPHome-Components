#include "PumpSwitch.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Pump Override Switch";

void PumpSwitch::write_state(bool state) {
    publish_state(state);
}

} //namespace sump_pump_controller
} //namespace esphome