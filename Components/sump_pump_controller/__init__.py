import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

SumpPumpController_ns = cg.esphome_ns.namespace("sump_pump_controller")
SumpPumpController = SumpPumpController_ns.class_("SumpPumpController", cg.Component)

# YAML keys used to configure this device
CONF_SUMP_PUMP_CONTROLLER_ID = "sump_pump_controller_ID"
# SUMP_DEPTH_KEY = "sump_depth" # in meters
# ENABLE_SWITCH_NAME_KEY = "enable_switch"
# CURRENT_SENSOR_NAME_KEY = "current_sensor"
# BATTERY_VOLTAGE_NAME_KEY = "battery_voltage"
# WATER_LEVEL_NAME_KEY = "water_level"

SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_SUMP_PUMP_CONTROLLER_ID): cv.use_id(SumpPumpController),
    }
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SumpPumpController),
        # cv.Required(CONF_ID): cv.use_id(SumpPumpController),
        # cv.Required(SUMP_DEPTH_KEY): cv.float_,
        # cv.Required(CONF_STATE): switch.switch_schema(switch.Switch),
        # # cv.Optional(ENABLE_SWITCH_NAME_KEY, default = "Enable Switch"): cv.string,
        # # cv.Optional(CURRENT_SENSOR_NAME_KEY, default = "Battery Current"): cv.string,
        # # cv.Optional(BATTERY_VOLTAGE_NAME_KEY, default = "Battery Voltage"): cv.string,
        # # cv.Optional(WATER_LEVEL_NAME_KEY, default = "Water Level"): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    controller = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(controller, config)
