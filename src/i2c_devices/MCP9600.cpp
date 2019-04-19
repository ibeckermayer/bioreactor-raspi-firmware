//
// Created by Isaiah Becker-Mayer on 2019-04-17.
//

#include "MCP9600.h"

std::unordered_map<std::string, int> MCP9600::registerPointer = {
        {"HOT_JUNCTION_TEMPERATURE",          0x00},
        {"STATUS",                            0x04},
        {"THERMOCOUPLE_SENSOR_CONFIGURATION", 0x05},
        {"DEVICE_CONFIGURATION",              0x06}
};

std::unordered_map<std::string, int> MCP9600::configurationValue = {
        {"THERMOCOUPLE_SENSOR_CONFIGURATION", 0x00},
        {"DEVICE_CONFIGURATION",              0x00}
};

MCP9600::MCP9600(int slaveAddress) : I2CSlave("MCP9600", slaveAddress) {
    configureThermocouple(configurationValue["THERMOCOUPLE_SENSOR_CONFIGURATION"]);
    configureDevice(configurationValue["DEVICE_CONFIGURATION"]);
}

void MCP9600::configureThermocouple(int config) {
    i2cWrite(EIGHT, registerPointer["THERMOCOUPLE_SENSOR_CONFIGURATION"], config);
}

void MCP9600::configureDevice(int config) {
    i2cWrite(EIGHT, registerPointer["DEVICE_CONFIGURATION"], config);
}

bool MCP9600::isInputRangeValid() {
    int res = i2cRead(EIGHT, registerPointer["STATUS"]);
    return !(res >> 4 & 1);
}

float MCP9600::tempReadToCelsius(int res) {
    // bytes are returned in reverse order, so must be extracted
    int upper_byte = res & 0x00ff;
    int lower_byte = (res & 0xff00) >> 8;

    // formula given in data sheet
    return ((float) upper_byte * 16.0) + ((float) lower_byte / 16.0);
}

float MCP9600::readTemp() {
    return tempReadToCelsius(i2cRead(SIXTEEN, registerPointer["HOT_JUNCTION_TEMPERATURE"]));
}

MCP9600::~MCP9600() = default;

