#include "BatteryChargerSwitch.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "Battery Charger Switch";

void BatteryChargerSwitch::write_state(bool state) {
    publish_state(state);
}

} //namespace sump_pump_controller
} //namespace esphome