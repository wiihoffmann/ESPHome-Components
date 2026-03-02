import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import switch

SumpPumpController_ns = cg.esphome_ns.namespace("sump_pump_controller")
SumpPumpController = SumpPumpController_ns.class_("sump_pump_controller", cg.Component)

AUTO_LOAD = ['switch']

# YAML keys used to configure this device
SUMP_DEPTH_KEY = "sump_depth" # in meters
ENABLE_SWITCH_NAME_KEY = "enable_switch"
CURRENT_SENSOR_NAME_KEY = "current_sensor"
BATTERY_VOLTAGE_NAME_KEY = "battery_voltage"
WATER_LEVEL_NAME_KEY = "water_level"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SumpPumpController),
        cv.Required(SUMP_DEPTH_KEY): cv.float_,
        cv.Optional(ENABLE_SWITCH_NAME_KEY, default = "Enable Switch"): cv.string,
        cv.Optional(CURRENT_SENSOR_NAME_KEY, default = "Battery Current"): cv.string,
        cv.Optional(BATTERY_VOLTAGE_NAME_KEY, default = "Battery Voltage"): cv.string,
        cv.Optional(WATER_LEVEL_NAME_KEY, default = "Water Level"): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
  #  sw = await switch.new_switch()
  #  state = await cg.get_variable(config[ENABLE_SWITCH_NAME_KEY])