/// @file API for interfacing with MCP9600 thermocouple chip via I2C

#ifndef FIRMWARE_MCP9600_H
#define FIRMWARE_MCP9600_H

#include <string>
#include <unordered_map>

using namespace std;

/// @brief MCP9600 class
class MCP9600 {
private:
    int devid; ///< I2C address
    int fd;
    static unordered_map<string, int> reg_map;
    void configure_device();
    void configure_thermocouple();
    float temp_read_to_C(int res);
    int setup_wiring_pi();

public:
    MCP9600();

    explicit MCP9600(int devid);

    ~MCP9600();

    bool input_range_valid();

    float read_temp();
};


#endif //FIRMWARE_MCP9600_H
