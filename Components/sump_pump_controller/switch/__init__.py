import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import DEVICE_CLASS_SWITCH
from .. import SumpPumpController_ns, CONF_SUMP_PUMP_CONTROLLER_ID, SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA

# Corresponding C++ class names, and which classes they extend.
ManualModeSwitch = SumpPumpController_ns.class_("ManualModeSwitch", switch.Switch, cg.Component)
PumpSwitch = SumpPumpController_ns.class_("PumpSwitch", switch.Switch, cg.Component)
BatteyChargerSwitch = SumpPumpController_ns.class_("BatteryChargerSwitch", switch.Switch, cg.Component)

# Icons shown in Home Assistant. Taken from Google's MDI icon library. https://pictogrammers.com/library/mdi/
ICON_MANUAL_MODE_SWITCH = "mdi:power"
ICON_PUMP_SWITCH = "mdi:pump"
ICON_BATTERY_CHARGER_SWITCH = "mdi:car-battery"

# key names used in the config.yaml file for the ESPHome device
CONF_MANUAL_MODE_SWITCH = "manual_mode_switch"
CONF_PUMP_SWITCH = "pump_switch"
CONF_BATTERY_CHARGER_SWITCH = "battery_charger_switch"

# Config.yaml key:value validation scheme
CONFIG_SCHEMA = SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA.extend({
    cv.Optional(CONF_MANUAL_MODE_SWITCH): switch.switch_schema(ManualModeSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_MANUAL_MODE_SWITCH, default_restore_mode="RESTORE_DEFAULT_ON"),
    cv.Optional(CONF_PUMP_SWITCH): switch.switch_schema(PumpSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_PUMP_SWITCH),
    cv.Optional(CONF_BATTERY_CHARGER_SWITCH): switch.switch_schema(BatteyChargerSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_BATTERY_CHARGER_SWITCH),
    #cv.Optional(CONF_BATTERY_CHARGER_SWITCH): switch.gpio_output_pin_schema(BatteyChargerSwitch, device_class=DEVICE_CLASS_SWITCH, icon=ICON_BATTERY_CHARGER_SWITCH),
})

async def to_code(config):
    SumpPumpController = await cg.get_variable(config[CONF_SUMP_PUMP_CONTROLLER_ID])

    if CONF_MANUAL_MODE_SWITCH in config:
        # Create a switch that is a child of the SumpPumpController object
        manualModeSW = await switch.new_switch(config[CONF_MANUAL_MODE_SWITCH])
        await cg.register_parented(manualModeSW, SumpPumpController)
        # Call the setEnableSwitch method in the C++ code to set the switch pointer variable
        cg.add(SumpPumpController.setEnableSwitch(manualModeSW))

    if CONF_PUMP_SWITCH in config:
        pumpSW = await switch.new_switch(config[CONF_PUMP_SWITCH])
        await cg.register_parented(pumpSW, SumpPumpController)
        cg.add(SumpPumpController.setPumpSwitch(pumpSW))

    if CONF_BATTERY_CHARGER_SWITCH in config:
        batteryChargerSW = await switch.new_switch(config[CONF_BATTERY_CHARGER_SWITCH])
        await cg.register_parented(batteryChargerSW, SumpPumpController)
        cg.add(SumpPumpController.setBatteryChargerSwitch(batteryChargerSW))