#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(53); //CS pin of the can bus (Uno usually use CS pin number 9 or 10), (Mega2560 use CS pin number 53), ...

#include <SmartDriver.h>

struct can_frame can_msg_transmit;

uint8_t commandData[8];

float desired_speed = 10;

SmartDriver motor;

void setup() {
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
    motor.speedMode = true;
    motor.stop = false;
    motor.reset = false;
    motor.voltageMode = false;
    motor.goal = desired_speed;
    motor.getCommand(commandData);

    can_msg_transmit.can_id = 0x03; // example ID for the motor controller
    can_msg_transmit.can_dlc = 8; // data length
    memcpy(can_msg_transmit.data, commandData, 8);

    mcp2515.sendMessage(&can_msg_transmit);
    
    delay(10);
}
