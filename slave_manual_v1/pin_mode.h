#include "Arduino.h"
#define min_value 282
#define mid_value 1002
#define max_value 1722

#define solen_G_up_R 35 //Solenoid Gripper up on the right
#define solen_G_do_R 34 //Solenoid Gripper down on the right
#define solen_G_L 38 //Solenoid Gripper up on the left
#define solen_S_up_R 31 //Solenoid Slider up on the right
#define solen_S_do_R 30 //Solenoid Slider down on the right


bool pickup_R = false;
bool motor_stop = false;
bool release = false;
bool ch5 = false;
bool ch9 = false;
bool griperRelease = false;
bool ch5MaxExecuted = false;
bool ch5MidExecuted = true;
bool ch9MaxExecuted = false;
bool ch9MinExecuted = true;
bool ch11MaxExecuted = false;
bool ch11MinExecuted = true;

unsigned long plantSealingStartTime = 0;
bool plantSealingStep1Done = false;

unsigned long plantSealingGStartTime = 0;
bool plantSealingGStep1Done = false;

enum State{
  EXTEND_SEALING,
  SHRINK_SEALING,
  GRAP_SEALING,
  RELEASE_SEALING,
  PLANT_SEALING,
  PLANT_SEALINGG
};

State currentState;



unsigned long previousMillis = 0;
const unsigned long interval = 3000; 

void solenoid_init(){
  pinMode(solen_G_up_R, OUTPUT);
  pinMode(solen_G_do_R, OUTPUT);  
  pinMode(solen_G_L, OUTPUT);  
  pinMode(solen_S_up_R, OUTPUT);  
  pinMode(solen_S_do_R, OUTPUT);  

}
void rs485_init() {
  rs485.begin(115200);
  rs485.setTimeout(100);
}