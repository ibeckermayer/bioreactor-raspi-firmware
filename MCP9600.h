//
// Created by Isaiah Becker-Mayer on 2019-04-17.
//

#ifndef FIRMWARE_MCP9600_H
#define FIRMWARE_MCP9600_H

#include <string>
#include <unordered_map>

using namespace std;

class MCP9600 {
private:
    int devid;
    int fd;
    static unordered_map<string, int> reg_map;

    void configure_device();

    void configure_thermocouple();

    static float temp_read_to_C(int res);

    int setup_wiring_pi();

public:
    MCP9600();

    explicit MCP9600(int devid);

    ~MCP9600();

    bool input_range_valid();

    float read_temp();
};


#endif //FIRMWARE_MCP9600_H
