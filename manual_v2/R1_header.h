#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include "sbus.h"
#include <SmartDriver.h>

/* SBUS object, reading SBUS */
bfs::SbusRx sbus_rx(&Serial1);
bfs::SbusData data;
String channels = "";
float M[4] = {0, 0, 0, 0};
struct can_frame canMsg;
MCP2515 mcp2515(53); //CS pin of the can bus (Uno usually use CS pin number 9 or 10), (Mega2560 use CS pin number 53), ...

struct can_frame can_msg_transmit;
struct can_frame can_msg_receive;

uint8_t commandData[8];
uint8_t receiveData[8];

float feedback_speed;
float feedback_position;


SmartDriver motor;