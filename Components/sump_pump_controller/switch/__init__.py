import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch

from .. import SumpPumpController_ns, SUMP_PUMP_CONTROLLER_ID

EnableSwitch = SumpPumpController_ns.class_("EnableSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.switch_schema(EnableSwitch).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)