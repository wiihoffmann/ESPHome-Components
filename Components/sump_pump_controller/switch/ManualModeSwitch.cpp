#include "ManualModeSwitch.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Manual Mode Switch";

void ManualModeSwitch::write_state(bool state) {
    publish_state(state);
}

} //namespace sump_pump_controller
} //namespace esphome