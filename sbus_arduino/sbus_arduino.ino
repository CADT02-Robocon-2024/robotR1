#include "sbus.h"

/* SBUS object, reading SBUS */
bfs::SbusRx sbus_rx(&Serial1);
bfs::SbusData data;
String channels = "";
void setup() {
  Serial.begin(115200);
  sbus_rx.Begin();

}

void loop() {
  channels = "";
  if (sbus_rx.Read()) {
    data = sbus_rx.data();
    for (int8_t i = 0; i < 12; i++) {
      Serial.print(i);
      Serial.print(":");
      Serial.print(data.ch[i]);
      Serial.print("\t");
    }
    Serial.println(channels);
  }

}

/*x1 -> 0
  y1 -> 1
  y2 -> 2
  x2 -> 3
  E  -> 4
  y3 -> 5
  x3 -> 6
  F  -> 7
  A  -> 8
  B  -> 9
  C  -> 10
  D  -> 11
*/
