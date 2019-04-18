/// @file I2CSlave.cpp
/// implementation of I2CSlave.h API

#include "I2CSlave.h"
#include "I2CSlaveError.h"
#include <wiringPiI2C.h>
#include <unistd.h>


I2CSlave::~I2CSlave() {
    close(fd);
}

int I2CSlave::getSlaveAddress() const {
    return slaveAddress;
}

I2CSlave::I2CSlave(const std::string &name, int slaveAddress) : name(name), slaveAddress(slaveAddress) {
    fd = wiringPiI2CSetup(slaveAddress);
    if (fd == -1) {
        throw I2CFileDescriptorError(name, slaveAddress);
    }
}

const std::string &I2CSlave::getName() const {
    return name;
}

void I2CSlave::i2cWrite(I2CSlave::I2CNumBits numBits, int reg, int data) {
    int res;

    if (numBits == EIGHT) {
        res = wiringPiI2CWriteReg8(fd, reg, data);
    } else {
        res = wiringPiI2CWriteReg16(fd, reg, data);
    }

//    if write error, throw error
    if (res) {
        throw I2CWriteError(name, slaveAddress);
    }
//    else do nothing, write succeeded
}

int I2CSlave::i2cRead(I2CSlave::I2CNumBits numBits, int reg) {
    int res;

    if (numBits == EIGHT) {
        res = wiringPiI2CReadReg8(fd, reg);
    } else {
        res = wiringPiI2CReadReg16(fd, reg);
    }

//    if read error, throw error
    if (res == -1) {
        throw I2CReadError(name, slaveAddress);
    } else {
        return res;
//        else return result
    }
}
