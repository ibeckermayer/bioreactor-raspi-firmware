#include "MCP9600.h"
#include <iostream>

using namespace std;

int main() {
    MCP9600 mcp = MCP9600(0x60);

    for (int i = 0; i < 10; i++) {
        printf("Temperature: %f Celsius\n", mcp.readTemp());
    }
}
