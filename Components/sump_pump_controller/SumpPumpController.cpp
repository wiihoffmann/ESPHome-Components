#include "esphome/core/log.h"
#include "SumpPumpController.h"

namespace esphome {
namespace sump_pump_controller {

static const char *TAG = "sump_pump_controller.component";

void SumpPumpContoller::setup() {
    // enableSW = new enable_switch::EnableSwitch();
    // enableSW->set_name("fart");
    // enableSW->set_internal(false);
    //enableSW.set_name("Enable Switch");
}

void SumpPumpContoller::loop() {

}

void SumpPumpContoller::dump_config(){
    ESP_LOGCONFIG(TAG, "Sump Pump Controller");
}

} //namespace sump_pump_controller
} //namespace esphome