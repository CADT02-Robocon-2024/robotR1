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

unsigned long previousMillis = 0;
const unsigned long interval = 2000; 

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