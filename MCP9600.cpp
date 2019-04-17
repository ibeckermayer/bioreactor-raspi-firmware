//
// Created by Isaiah Becker-Mayer on 2019-04-17.
//

#include <cstdio>
#include <unistd.h>
#include <wiringPiI2C.h>
#include "MCP9600.h"

void MCP9600::configure_device() {
    wiringPiI2CWriteReg8(fd, reg_map["DEVICE_CONFIG"], 0x00); // TODO exception if != 0
}

void MCP9600::configure_thermocouple() {
    wiringPiI2CWriteReg8(fd, reg_map["THERMOCOUPLE_CONFIG"], 0x00); // TODO exception if != 0
}

float MCP9600::temp_read_to_C(int res) {
    // bytes are returned in reverse order, so must be extracted
    int upper_byte = res & 0x00ff;
    int lower_byte = (res & 0xff00) >> 8;
    // TODO check that result is not negative, indicated by MSB. If it is, should
    // return same formula but -4096, see datasheet
    return ((float) upper_byte * 16.0) + ((float) lower_byte / 16.0); // formula given in data sheet
}

MCP9600::MCP9600() {
    this->devid = 0x60;
    this->fd = setup_wiring_pi();
    configure_thermocouple();
    configure_device();
}

MCP9600::MCP9600(int devid) {
    this->devid = devid;
    this->fd = setup_wiring_pi();
    configure_thermocouple();
    configure_device();
}

MCP9600::~MCP9600() {
    close(this->fd);
}

bool MCP9600::input_range_valid() {
    int res = wiringPiI2CReadReg8(fd, reg_map["STATUS"]); // TODO exception if -1
    return !(res >> 4 & 1);
}

float MCP9600::read_temp() {
    // TODO should check that input_range is valid and if not, raise an exception
    // This check may be overzealous for every single read

    // TODO can also read bit-6 on the STATUS register until it's 1, which
    // indicates temperature conversion is complete and ready to be read. Probably
    // would want to poll this bit a max of (say) 10 times and if it's
    // consistently 0 then raise an error.
    int res = wiringPiI2CReadReg16(fd, reg_map["HOT_JUNCTION"]); // TODO exception if -1
    return temp_read_to_C(res);
}

int MCP9600::setup_wiring_pi() {
    return wiringPiI2CSetup(this->devid);
}

// map of device register names to values
unordered_map<string, int> MCP9600::reg_map = {{"HOT_JUNCTION",        0x00},
                                               {"STATUS",              0x04},
                                               {"THERMOCOUPLE_CONFIG", 0x05},
                                               {"DEVICE_CONFIG",       0x06}};

