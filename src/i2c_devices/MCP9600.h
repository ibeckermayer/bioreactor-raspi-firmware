/// @file MCP9600.h
/// class for controlling MCP9600 thermocouple reader
/// datasheet can be found at http://ww1.microchip.com/downloads/en/DeviceDoc/MCP9600-Data-Sheet-DS20005426D.pdf

#ifndef FIRMWARE_MCP9600_H
#define FIRMWARE_MCP9600_H


#include "I2CSlave.h"
#include <unordered_map>
#include <string>

class MCP9600 : public I2CSlave {
private:
    /// @brief Configures sensor measurement resolutions and Power modes
    /// @param[in] config configuration code
    /// @note see REGISTER 5-8 in the datasheet for details
    /// @throws I2CWriteError
    void configureDevice(int config);

    /// @brief Select the thermocouple sensor type and digital filter options
    /// @param config configuration code
    /// @note see REGISTER 5-7 in the datasheet for details
    /// @throws I2CWriteError
    void configureThermocouple(int config);

    /// @brief Converts integer read over i2c to a temperature in Celsius
    /// @param res integer read over i2c from REGISTER 5-2
    /// @note assumes (temperature >= 0 Celsius). Conversion is different for negative temperatures, see EQUATION 5-1
    /// in datasheet for details
    /// @return temperature in degrees Celsius
    float tempReadToCelsius(int res);

    /// @brief Map of descriptive register names to pointer values. See TABLE 5-1 in datasheet for details.
    /// @warning names should correspond to names in configurationValue map for clarity
    static std::unordered_map<std::string, int> registerPointer;

    /// @brief Map of descriptive register names to configuration values.
    /// @warning names should correspond to names in registerPointer map for clarity
    static std::unordered_map<std::string, int> configurationValue;

public:
    /// @brief destructor
    virtual ~MCP9600();

    /// @brief constructor, calls I2CSlave constructor with name as "MCP9600"
    /// @param slaveAddress[in] i2c address of the slave device
    /// @throws I2CFileDescriptorError
    /// @throws I2CWriteError
    MCP9600(int slaveAddress);

    /// @brief Checks that the ADC input Voltage (EMF) or the temperature data from the TH register is within the
    /// measurement range for the selected thermocouple type
    /// @warning If false, the  MCP9600/L00 does not convert the input voltage (EMF) to Degree Celsius
    /// (temperature data conversion is bypassed). The T∆, TH and TC registers hold the previous temperature data.
    /// @note This function should be called periodically to check that device is functioning properly. See REGISTER
    /// 5-6 in the datasheet for details.
    /// @return true if range is valid, false otherwise
    /// @throws I2CReadError
    bool isInputRangeValid();

    /// @brief Takes a temperature reading from the device
    /// @return Temperature read in degrees Celsius
    /// @note This function could theoretically poll bit 6 on REGISTER 5-6 to ensure that temperature conversion is
    /// complete. For now we are assuming that our system is low enough latency that this is unnecessary.
    /// @note See REGISTER 5-2 in the datasheet for details
    /// @throws I2CReadError
    float readTemp();
};


#endif //FIRMWARE_MCP9600_H
