/// @file I2CSlave.h
/// Common Base class for interfacing with i2c slaves using wiringPi
/// The author of wiringPi claims that it's thread-safe:
/// https://www.raspberrypi.org/forums/viewtopicphp?t=136118. This means that we should be able to safely read/write
/// to multiple i2c slaves over "/dev/i2c-1" without issue. Therefore we can simply create multiple instances of this
/// class to communicate to multiple devices and not have to worry about race conditions etc.

#ifndef FIRMWARE_I2CSLAVE_H
#define FIRMWARE_I2CSLAVE_H

#include <string>

/// @brief I2CSlave class
class I2CSlave {
private:
    /// @brief name of the I2C device
    std::string name;

    /// @brief i2c address for given slave device
    int slaveAddress;

    /// @brief file descriptor to written to / read from. Each slave address is given it's own file descriptor by
    /// wiringPi.
    int fd;

protected:
    /// @brief number of bits to read/write for i2c read or write
    enum I2CNumBits {
        EIGHT,
        SIXTEEN
    };

public:
    /// @brief constructor
    /// @param[in] name descriptive name for the device
    /// @param[in] slaveAddress i2c address for this device
    /// @throws I2CFileDescriptorError
    I2CSlave(const std::string &name, int slaveAddress);

    /// @brief closes file descriptor (this->fd)
    virtual ~I2CSlave();

    /// @brief getter
    /// @return this->slave_address
    int getSlaveAddress() const;

    /// @brief getter
    /// @return this->name
    const std::string &getName() const;

    /// @brief i2c write function
    /// @param numBits number of bits to write
    /// @param reg device register to write to
    /// @param data data to write to reg
    /// @throws I2CWriteError
    void i2cWrite(I2CNumBits numBits, int reg, int data);

    /// @brief i2c read function
    /// @param numBits number of bits to read
    /// @param reg register to read from
    /// @return data read
    /// @throws I2cReadError
    int i2cRead(I2CNumBits numBits, int reg);



};


#endif //FIRMWARE_I2CSLAVE_H
