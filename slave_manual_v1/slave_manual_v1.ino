#include "slave_header.h"
#include "pin_mode.h"

#define SLAVE_ADDRESS 8 // Address of this Arduino as slave
int sbusData[12]; // Array to store received SBUS data

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

void setup() {
  pc.begin(115200);
  pc.setTimeout(100);
  pc.flush();
  Wire.begin(SLAVE_ADDRESS); // Initialize I2C communication as Slave
  Wire.onReceive(receiveData); // Register callback for receiving data
  solenoid_init();
  rs485_init();
  runMulti_Angle_speed(1,0,200);
  runMulti_Angle_speed(2,0,200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // if(sbusData[])
  // printsbus();
  solenoid_control();

}
void solenoid_control() {
  if (sbusData[5] == max_value){
    slider(1);
  }else{
    slider(0);
  }
  if (sbusData[9] == max_value) {
    grab_sealing_right(1);
    pick_up_motorR(200);
    pickup_R = true;
  }else{
    if(pickup_R == true){
      pick_up_motorR(0);
      delay(500);
      grab_sealing_right(0);
    }

  }
}

void pick_up_motorL(int position){
  runMulti_Angle_speed(1,position,400);
}

void pick_up_motorR(int position){
  runMulti_Angle_speed(2,position,400);
}
void grab_sealing_left() {
  left_griper(1);
}
void grab_sealing_right(bool value) {
  right_up_griper(value);
  right_do_griper(value);
}
