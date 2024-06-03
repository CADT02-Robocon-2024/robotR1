// SmartDriver.cpp
#include "SmartDriver.h"

SmartDriver::SmartDriver() : speedMode(false), stop(false), reset(false), voltageMode(false), goal(0.0f) {}

void SmartDriver::getCommand(uint8_t *data) {
    memset(data, 0, 8); // Clear the existing data
    data[0] = speedMode + (stop << 1) + (reset << 2) + (voltageMode << 3);
    memcpy(&data[2], &goal, sizeof(float)); // Copy goal float into data starting at index 2
}
