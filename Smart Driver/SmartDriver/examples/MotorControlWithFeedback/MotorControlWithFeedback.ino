#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(53); //CS pin of the can bus (Uno usually use CS pin number 9 or 10), (Mega2560 use CS pin number 53), ...

#include <SmartDriver.h>

struct can_frame can_msg_transmit;
struct can_frame can_msg_receive;

uint8_t commandData[8];
uint8_t receiveData[8];

float feedback_speed;
float feedback_position;

float desired_speed = 0;

SmartDriver motor;

void setup() {
  // Serial.begin(115200);
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

    can_msg_transmit.can_id = 0x01; // example ID for the motor controller
    can_msg_transmit.can_dlc = 8; // data length code
    memcpy(can_msg_transmit.data, commandData, 8);
    mcp2515.sendMessage(&can_msg_transmit);

    if (mcp2515.readMessage(&can_msg_receive) == MCP2515::ERROR_OK) {  
      if (can_msg_receive.can_id == 254){
        memcpy(&feedback_position, can_msg_receive.data, sizeof(float));
        memcpy(&feedback_speed, can_msg_receive.data + 4, sizeof(float));
        Serial.println(feedback_position);
        Serial.println(feedback_speed);
      }
    }
    delay(10);
}
