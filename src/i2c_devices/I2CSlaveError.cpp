/// @file I2CSlaveError.cpp

#include "I2CSlaveError.h"
#include <sstream>


I2CSlaveError::I2CSlaveError(const std::string &prefix, const std::string &name,
                             int slaveAddress) : runtime_error(buildErrorMsg(prefix, name, slaveAddress)) {
}

I2CSlaveError::~I2CSlaveError() = default;

const std::string I2CSlaveError::buildErrorMsg(const std::string &prefix, const std::string &name, int slaveAddress) {
    std::stringstream ss;
    ss << slaveAddress;
    return prefix + name + "at slaveAddress " + ss.str();
}


I2CFileDescriptorError::I2CFileDescriptorError(const std::string &name, int slaveAddress) : I2CSlaveError(
        "Could not get file descriptor for device ", name, slaveAddress) {}

I2CReadError::I2CReadError(const std::string &name, int slaveAddress) : I2CSlaveError("Read failed for device ", name,
                                                                                      slaveAddress) {}

I2CWriteError::I2CWriteError(const std::string &name, int slaveAddress) : I2CSlaveError("Write failed for device ",
                                                                                        name,
                                                                                        slaveAddress) {}