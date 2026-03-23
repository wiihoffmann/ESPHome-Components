import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output, binary_sensor
from esphome.const import CONF_ID

SumpPumpController_ns = cg.esphome_ns.namespace("sump_pump_controller")
SumpPumpController = SumpPumpController_ns.class_("SumpPumpController", cg.Component)

AUTO_LOAD = ["switch"]

# Icons shown in Home Assistant. Taken from Google's MDI icon library. https://pictogrammers.com/library/mdi/
ICON_WATER_LEVEL = "mdi:waves-arrow-up"
ICON_BATTERY_VOLTAGE = "mdi:car-battery"
ICON_BATTERY_CURRENT = "mdi:car-battery"

# key names used in the config.yaml file for the ESPHome device
CONF_SUMP_PUMP_CONTROLLER_ID = "sump_pump_controller_ID"
CONF_SUMP_DEPTH = "sump_depth"
CONF_HIGH_LIMIT = "high_limit"
CONF_LOW_LIMIT = "low_limit"
CONF_CHARGER_CUT_IN = "charger_cut_in"
CONF_CHARGER_CUT_OUT = "charger_cut_out"
CONF_CHARGE_TIME = "charge_time"
CONF_LEVEL_SENSOR_ID = "ultrasonic_sensor_id"
CONF_RED_LED_ID = "red_led_id"
CONF_GREEN_LED_ID = "green_led_id"
CONF_CHARGE_FET_ID = "charge_fet_id"
CONF_PUMP_FET_ID = "pump_fet_id"
CONF_MANUAL_SWITCH_ID = "mode_switch_id"
CONF_CURRENT_SENSOR_ID = "current_sensor_id"
CONF_BATTERY_VOLTAGE_ID = "battery_voltage_id"
CONF_TICK_RATE = "tick_rate"
CONF_PUBLISH_RATE = "publish_rate"
CONF_BATTEY_VOLTAGE_SENSOR = "battery_voltage_sensor"
CONF_BATERY_CURRENT_SENSOR = "battery_current_sensor"
CONF_WATER_LEVEL_SENSOR = "water_level_sensor"

# All child components will extend this schema. Children which reference this SumpPumpController ID are owned by this SumpPumpController
SUMP_PUMP_CONTROLLER_COMPONENT_SCHEMA = cv.Schema({
    cv.Required(CONF_SUMP_PUMP_CONTROLLER_ID): cv.use_id(SumpPumpController),
})

# Config.yaml key:value validation scheme
CONFIG_SCHEMA = cv.Schema({
        cv.GenerateID(): cv.declare_id(SumpPumpController),

        cv.Required(CONF_SUMP_DEPTH): cv.distance,
        cv.Required(CONF_HIGH_LIMIT): cv.distance,
        cv.Required(CONF_LOW_LIMIT): cv.distance,
        cv.Required(CONF_RED_LED_ID): cv.use_id(output.BinaryOutput),
        cv.Required(CONF_GREEN_LED_ID): cv.use_id(output.BinaryOutput),
        cv.Required(CONF_CHARGE_FET_ID): cv.use_id(output.BinaryOutput),
        cv.Required(CONF_PUMP_FET_ID): cv.use_id(output.BinaryOutput),
        cv.Required(CONF_CURRENT_SENSOR_ID): cv.use_id(sensor.Sensor),
        cv.Required(CONF_BATTERY_VOLTAGE_ID): cv.use_id(sensor.Sensor),
        cv.Required(CONF_MANUAL_SWITCH_ID): cv.use_id(binary_sensor.BinarySensor),
        cv.Required(CONF_LEVEL_SENSOR_ID): cv.use_id(sensor.Sensor),

        cv.Optional(CONF_CHARGER_CUT_IN, default="12.4 v"): cv.voltage,
        cv.Optional(CONF_CHARGER_CUT_OUT, default="14.5 v"): cv.voltage,
        cv.Optional(CONF_CHARGE_TIME, default="2 h"): cv.positive_time_period_seconds,
        cv.Optional(CONF_PUBLISH_RATE, default="30 s"): cv.positive_time_period_seconds,
        cv.Optional(CONF_TICK_RATE, default="1 s"): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_BATTEY_VOLTAGE_SENSOR): cv.Schema(sensor.sensor_schema(icon=ICON_BATTERY_VOLTAGE, accuracy_decimals=2, unit_of_measurement="V")),
        cv.Optional(CONF_BATERY_CURRENT_SENSOR): cv.Schema(sensor.sensor_schema(icon=ICON_BATTERY_CURRENT, accuracy_decimals=2, unit_of_measurement="A")),
        cv.Optional(CONF_WATER_LEVEL_SENSOR): cv.Schema(sensor.sensor_schema(icon=ICON_WATER_LEVEL, accuracy_decimals=1, unit_of_measurement="cm")),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    controller = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(controller, config)

    cg.add(controller.setSumpDepthm(config[CONF_SUMP_DEPTH]))
    cg.add(controller.setHighLimitm(config[CONF_HIGH_LIMIT]))
    cg.add(controller.setLowLimitm(config[CONF_LOW_LIMIT]))
    cg.add(controller.setChargerCutIn(config[CONF_CHARGER_CUT_IN]))
    cg.add(controller.setChargerCutOut(config[CONF_CHARGER_CUT_OUT]))
    cg.add(controller.setMaxChargeTime(config[CONF_CHARGE_TIME]))

    pinID = await cg.get_variable(config[CONF_RED_LED_ID])
    cg.add(controller.setRedLEDPin(pinID))
    pinID = await cg.get_variable(config[CONF_GREEN_LED_ID])
    cg.add(controller.setGreenLEDPin(pinID))
    pinID = await cg.get_variable(config[CONF_CHARGE_FET_ID])
    cg.add(controller.setChargeFETPin(pinID))
    pinID = await cg.get_variable(config[CONF_PUMP_FET_ID])
    cg.add(controller.setPumpFETPin(pinID))
    pinID = await cg.get_variable(config[CONF_MANUAL_SWITCH_ID])
    cg.add(controller.setManualSwitchPin(pinID))
    levelSensor = await cg.get_variable(config[CONF_LEVEL_SENSOR_ID])
    cg.add(controller.setDistanceSensor(levelSensor))
    sense = await cg.get_variable(config[CONF_CURRENT_SENSOR_ID])
    cg.add(controller.setInternalCurrentSensor(sense))
    sense = await cg.get_variable(config[CONF_BATTERY_VOLTAGE_ID])
    cg.add(controller.setInternalVoltageSensor(sense))
    
    if CONF_BATTEY_VOLTAGE_SENSOR in config:
        sense = await sensor.new_sensor(config[CONF_BATTEY_VOLTAGE_SENSOR])
        cg.add(controller.setDashboardVoltageSensor(sense))
    if CONF_BATERY_CURRENT_SENSOR in config:
        sense = await sensor.new_sensor(config[CONF_BATERY_CURRENT_SENSOR])
        cg.add(controller.setDashboardCurrentSensor(sense))
    if CONF_WATER_LEVEL_SENSOR in config:
        sense = await sensor.new_sensor(config[CONF_WATER_LEVEL_SENSOR])
        cg.add(controller.setDashboardCurrentSensor(sense))