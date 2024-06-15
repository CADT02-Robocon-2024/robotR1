#include "slave_header.h"
#include "pin_mode.h"

// #define SLAVE_ADDRESS 8 // Address of this Arduino as slave
// int sbusData[12]; // Array to store received SBUS data

/*x1 -> 0
  y1 -> 1
  y2 -> 2
  x2 -> 3
  E  -> 4
  G  -> 5
  H  -> 6
  F  -> 7
  A  -> 8
  B  -> 9
  C  -> 10
  D  -> 11
*/
String channel;
const unsigned long eventInterval = 2000;
unsigned long previousTime = 0;
void setup() {
  pc.begin(115200);
  pc.setTimeout(100);
  pc.flush();
  sbus_rx.Begin();
  // Wire.begin(SLAVE_ADDRESS); // Initialize I2C communication as Slave
  // Wire.onReceive(receiveData); // Register callback for receiving data
  solenoid_init();
  rs485_init();
  runMulti_Angle_speed(1, 0, 200);
  runMulti_Angle_speed(2, 0, 200);
  Serial.print("Done");
}

void loop() {

  // put your main code here, to run repeatedly:
  // if(sbusData[])
  // printsbus();
  if (sbus_rx.Read()) {
    data = sbus_rx.data();
    // sbus_data();
    // Serial.println("sbus");
    // sbus_tran();
  }
  if (data.ch[8] == max_value) {
    if (data.ch[6] == max_value && !ch5MaxExecuted) {
      Serial.println("5 max");
      currentState = EXTEND_SEALING;
      solenoid_control();
      ch5MaxExecuted = true;
      ch5MidExecuted = false;  // Resetting the opposite condition flag
    } else if (data.ch[6] == mid_value && !ch5MidExecuted) {
      Serial.println("5 mid");
      currentState = SHRINK_SEALING;
      solenoid_control();
      ch5MidExecuted = true;
      ch5MaxExecuted = false;  // Resetting the opposite condition flag
    }

    if (data.ch[9] == max_value && !ch9MaxExecuted) {
      Serial.println("9 max");
      currentState = GRAP_SEALING;
      solenoid_control();
      ch9MaxExecuted = true;
      ch9MinExecuted = false;  // Resetting the opposite condition flag
    } else if (data.ch[9] == min_value && !ch9MinExecuted) {
      Serial.println("9 min");
      currentState = RELEASE_SEALING;
      solenoid_control();
      ch9MinExecuted = true;
      ch9MaxExecuted = false;  // Resetting the opposite condition flag
    }

    if (data.ch[11] == max_value && !ch11MaxExecuted) {
      currentState = PLANT_SEALING;
      solenoid_control();
      ch11MaxExecuted = true;
      ch11MinExecuted = false;  // Resetting the opposite condition flag
    } else if (data.ch[11] == min_value && !ch11MinExecuted) {
      currentState = PLANT_SEALINGG;
      solenoid_control();
      ch11MinExecuted = true;
      ch11MaxExecuted = false;  // Resetting the opposite condition flag
    }
  }
}
void solenoid_control() {
  // Serial.println(currentState);
  switch (currentState) {
    case EXTEND_SEALING:
      Serial.println("5 max");
      slider(1);
      pick_up_motorL(0);
      break;
    case SHRINK_SEALING:
      Serial.println("5 mid");
      slider(0);
      break;
    case GRAP_SEALING:
      grab_sealing_right(1);
      pick_up_motorL(180);
      delayForSeconds(1);
      right_up_slider(0);
      delayForSeconds(1);
      pick_up_motorL(30);
      break;
    case RELEASE_SEALING:
      grab_sealing_right(0);
      pick_up_motorL(0);
      slider(1);
      break;
    case PLANT_SEALING:
      Serial.println("11 max");
      right_up_griper(0);
      delayForSeconds(1);
      right_do_slider(0);
      right_up_slider(1);      
      break;
    case PLANT_SEALINGG:
      Serial.println("11 min");
      right_do_griper(0);
      break;
    default:
      break;
  }
}

void pick_up_motorL(int position) {
  runMulti_Angle_speed(1, position, 1000);
}

void pick_up_motorR(int position) {
  runMulti_Angle_speed(2, position, 1000);
}
void grab_sealing_left() {
  left_griper(1);
}
void grab_sealing_right(bool value) {
  right_up_griper(value);
  right_do_griper(value);
}
void delayForSeconds(unsigned int seconds) {
  unsigned long end = millis() + seconds * 1000;
  while (millis() < end) {
    // Do nothing, just wait
  }
}
