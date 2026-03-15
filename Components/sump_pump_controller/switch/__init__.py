import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import DEVICE_CLASS_SWITCH
from .. import SumpPumpController_ns, CONF_SUMP_PUMP_CONTROLLER_ID, SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA

ManualModeSwitch = SumpPumpController_ns.class_("ManualModeSwitch", switch.Switch, cg.Component)
PumpSwitch = SumpPumpController_ns.class_("PumpSwitch", switch.Switch, cg.Component)
BatteyChargerSwitch = SumpPumpController_ns.class_("BatteryChargerSwitch", switch.Switch, cg.Component)

ICON_MANUAL_MODE_SWITCH = "mdi:power"
ICON_PUMP_SWITCH = "mdi:pump"
ICON_BATTERY_CHARGER_SWITCH = "mdi:car-battery"

CONF_MANUAL_MODE_SWITCH = "manual_mode_switch"
CONF_PUMP_SWITCH = "pump_switch"
CONF_BATTERY_CHARGER_SWITCH = "battery_charger_switch"

CONFIG_SCHEMA = SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA.extend({
    cv.Optional(CONF_MANUAL_MODE_SWITCH): switch.switch_schema(ManualModeSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_MANUAL_MODE_SWITCH, default_restore_mode="RESTORE_DEFAULT_ON"),
    cv.Optional(CONF_PUMP_SWITCH): switch.switch_schema(PumpSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_PUMP_SWITCH),
    cv.Optional(CONF_BATTERY_CHARGER_SWITCH): switch.switch_schema(BatteyChargerSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_BATTERY_CHARGER_SWITCH),
})

async def to_code(config):
    SumpPumpController = await cg.get_variable(config[CONF_SUMP_PUMP_CONTROLLER_ID])
    
    if CONF_MANUAL_MODE_SWITCH in config:
        manualModeSW = await switch.new_switch(config[CONF_MANUAL_MODE_SWITCH])
        await cg.register_parented(manualModeSW, SumpPumpController)
        cg.add(SumpPumpController.setEnableSwitch(manualModeSW))

    if CONF_PUMP_SWITCH in config:
        pumpSW = await switch.new_switch(config[CONF_PUMP_SWITCH])
        await cg.register_parented(pumpSW, SumpPumpController)
        cg.add(SumpPumpController.setPumpSwitch(pumpSW))

    if CONF_BATTERY_CHARGER_SWITCH in config:
        batteryChargerSW = await switch.new_switch(config[CONF_BATTERY_CHARGER_SWITCH])
        await cg.register_parented(batteryChargerSW, SumpPumpController)
        cg.add(SumpPumpController.setBatteryChargerSwitch(batteryChargerSW))