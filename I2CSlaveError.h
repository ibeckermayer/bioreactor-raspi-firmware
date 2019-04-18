/// @file I2CSlaveError.h
/// Exception definitions for I2CSlave class.

#ifndef FIRMWARE_I2CSLAVEERROR_H
#define FIRMWARE_I2CSLAVEERROR_H

#include <stdexcept>

/// @brief runtime error for I2CSlave objects
class I2CSlaveError : public std::runtime_error {
public:
    /// @brief constructor
    /// @param[in] prefix prefix of the error message
    /// @param[in] name name of the device
    /// @param[in] slaveAddress address of the device
    I2CSlaveError(const std::string &prefix, const std::string &name,
                  int slaveAddress);

    /// @brief static function for building error message to pass to runtime_error
    /// @param[in] prefix prefix of the error message
    /// @param[in] name name of the device
    /// @param[in] slaveAddress address of the device
    /// @return string of prefix + name + "at address " + str2hex(address)
    static const std::string buildErrorMsg(const std::string &prefix, const std::string &name, int slaveAddress);

    virtual ~I2CSlaveError();
};

/// @brief Error if file descriptor for I2C device could not be obtained
class I2CFileDescriptorError : public I2CSlaveError {
public:
    /// @brief constructor
    /// @param[in] name name for the device
    /// @param[in] slaveAddress address of device
    I2CFileDescriptorError(const std::string &name, int slaveAddress);
};

/// @brief Error for failed i2c read
class I2CReadError : public I2CSlaveError {
public:
    /// @brief constructor
    /// @param[in] name name for the device
    /// @param[in] slaveAddress address of device
    I2CReadError(const std::string &name, int slaveAddress);
};

/// @brief Error for failed i2c write
class I2CWriteError : public I2CSlaveError {
public:
    /// @brief constructor
    /// @param[in] name name for the device
    /// @param[in] slaveAddress address of device
    I2CWriteError(const std::string &name, int slaveAddress);
};


#endif //FIRMWARE_I2CSLAVEERROR_H
