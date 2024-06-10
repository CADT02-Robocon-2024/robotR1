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

void setup() {
  pc.begin(115200);
  pc.setTimeout(100);
  pc.flush();
  sbus_rx.Begin();
  // Wire.begin(SLAVE_ADDRESS); // Initialize I2C communication as Slave
  // Wire.onReceive(receiveData); // Register callback for receiving data
  solenoid_init();
  rs485_init();
  runMulti_Angle_speed(1,0,200);
  runMulti_Angle_speed(2,0,200);
  Serial.print("Done");
}

void loop() {
  // put your main code here, to run repeatedly:
  // if(sbusData[])
  // printsbus();
  if (sbus_rx.Read()) {
    data = sbus_rx.data();
    sbus_data();
    // Serial.println("sbus");
    // sbus_tran();
  }
  if (data.ch[8] == max_value) {
    // sbus_tran();
    solenoid_control();  
        
  }else{
    ch5 = true;
    ch9 = true;
  }
  
}
void solenoid_control() {
  if(ch5 == true){
    if (data.ch[5] == max_value){
      slider(1);
      ch5 = false;
    }else{
      slider(0);
    }
  }
  if(ch9 == true){
    if (data.ch[9] == max_value) {
      grab_sealing_right(1);
      pick_up_motorR(180);
      pickup_R = true;
      ch9 = false;
    }else if(data.ch[9] == min_value){
      if(pickup_R == true){
        pick_up_motorR(0);
        motor_stop = true;
        if(motor_stop == true){
          grab_sealing_right(0);
        }
        
      }
    }
  }
  
  if(data.ch[11] == max_value){
    right_up_slider(0);
    right_up_griper(0);
    release = true;

  }else if(data.ch[11] == min_value) {
    if (release == true){
      right_do_slider(0);
      right_up_slider(1);
      right_do_griper(0);
      release = false;
    }
    
  }
}
  


void pick_up_motorL(int position){
  runMulti_Angle_speed(1,position,1000);
}

void pick_up_motorR(int position){
  runMulti_Angle_speed(2,position,1000);
}
void grab_sealing_left() {
  left_griper(1);
}
void grab_sealing_right(bool value) {
  right_up_griper(value);
  right_do_griper(value);
}
