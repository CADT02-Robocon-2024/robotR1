#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(10); //CS pin of the can bus (Uno usually use CS pin number 9 or 10), (Mega2560 use CS pin number 53), ...

#include <SmartDriver.h>

struct can_frame can_msg_receive;

uint8_t receiveData[8];

float feedback_speed;
float feedback_position;

SmartDriver motor;

void setup() {
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
    if (mcp2515.readMessage(&can_msg_receive) == MCP2515::ERROR_OK) {  
      if (can_msg_receive.can_id == 254){
        memcpy(&feedback_position, can_msg_receive.data, sizeof(float));
        memcpy(&feedback_speed, can_msg_receive.data + 4, sizeof(float));
        //Serial.print(feedback_position);
        //Serial.print(feedback_speed);
      }
    }
    delay(10);
}
