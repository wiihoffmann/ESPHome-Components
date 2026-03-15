import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_NAME, CONF_STATE, CONF_INTERNAL, ENTITY_CATEGORY_CONFIG
from esphome.components import switch

SumpPumpController_ns = cg.esphome_ns.namespace("sump_pump_controller")
SumpPumpController = SumpPumpController_ns.class_("SumpPumpController", cg.Component)

AUTO_LOAD = ['switch']

# YAML keys used to configure this device
SUMP_PUMP_CONTROLLER_ID = "SumpPumpController_ID"
SUMP_DEPTH_KEY = "sump_depth" # in meters
ENABLE_SWITCH_NAME_KEY = "enable_switch"
CURRENT_SENSOR_NAME_KEY = "current_sensor"
BATTERY_VOLTAGE_NAME_KEY = "battery_voltage"
WATER_LEVEL_NAME_KEY = "water_level"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SumpPumpController),
        cv.Required(SUMP_DEPTH_KEY): cv.float_,
        cv.Required(CONF_STATE): switch.switch_schema(switch.Switch),
        # cv.Optional(ENABLE_SWITCH_NAME_KEY, default = "Enable Switch"): cv.string,
        # cv.Optional(CURRENT_SENSOR_NAME_KEY, default = "Battery Current"): cv.string,
        # cv.Optional(BATTERY_VOLTAGE_NAME_KEY, default = "Battery Voltage"): cv.string,
        # cv.Optional(WATER_LEVEL_NAME_KEY, default = "Water Level"): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    enable_switch = await switch.new_switch(
        {
            CONF_NAME: "Sump Pump Enable",
        }
    )