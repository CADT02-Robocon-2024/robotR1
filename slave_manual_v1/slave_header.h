#include <Wire.h>
#include "sbus.h"


#define pc Serial
#define rs485 Serial3
bfs::SbusRx sbus_rx(&Serial2);
bfs::SbusData data;
String channels = "";
byte mreply[] = {};
