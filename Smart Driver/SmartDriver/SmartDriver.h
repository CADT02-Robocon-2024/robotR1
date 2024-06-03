// SmartDriver.h
#ifndef SmartDriver_h
#define SmartDriver_h

#include "Arduino.h"

class SmartDriver {
public:
    bool speedMode;
    bool stop;
    bool reset;
    bool voltageMode;
    float goal;

    SmartDriver();
    void getCommand(uint8_t *data);
};

#endif
