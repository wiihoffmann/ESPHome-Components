#include "esphome/core/log.h"
#include "sump_pump_controller.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "sump_pump_controller.component";

void sump_pump_controller::setup() {
    enableSW = new enable_switch::EnableSwitch();
    enableSW->set_name("fart");
    enableSW->set_internal(false);
    //enableSW.set_name("Enable Switch");
}

void sump_pump_controller::loop() {

}

void sump_pump_controller::dump_config(){
    ESP_LOGCONFIG(TAG, "Sump Pump Controller");
}

} //namespace sump_pump_controller
} //namespace esphome