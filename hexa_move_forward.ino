#include <HardwareSerial.h>

#define RX_PIN 44
#define TX_PIN 43

/* HEXA Layout
 *  
 *   4 3
 *  5 o 2
 *   6 1
 *   
 Group A - odd
 Group B - even
 *   Minimum Amperage Needed: 3A
 */

// declare Hexa Motor Pins on Motor Driver
int leg1_body = 26;
int leg1_middle = 25;
int leg1_foot = 24;

int leg2_body = 22;
int leg2_middle = 21;
int leg2_foot = 20;

int leg3_body = 18;
int leg3_middle = 17;
int leg3_foot = 16;

int leg4_body = 2;
int leg4_middle = 1;
int leg4_foot = 0;

int leg5_body = 6;
int leg5_middle = 4;
int leg5_foot = 5;

int leg6_body = 10;
int leg6_middle = 9;
int leg6_foot = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();

  // Move all motors to starting position
  moveMotorCommand(leg1_body, 1500, 1000, 0);
  moveMotorCommand(leg2_body, 1500, 1000, 0);
  moveMotorCommand(leg3_body, 1500, 1000, 0);
  moveMotorCommand(leg4_body, 1500, 1000, 0);
  moveMotorCommand(leg5_body, 1500, 1000, 0);
  moveMotorCommand(leg6_body, 1500, 1000, 0);

  moveMotorCommand(leg1_middle, 1700, 1000, 0);
  moveMotorCommand(leg2_middle, 1700, 1000, 0);
  moveMotorCommand(leg3_middle, 1700, 1000, 0);
  moveMotorCommand(leg4_middle, 1700, 1000, 0);
  moveMotorCommand(leg5_middle, 1700, 1000, 0);
  moveMotorCommand(leg6_middle, 1700, 1000, 0);

  moveMotorCommand(leg1_foot, 1500, 1000, 0);
  moveMotorCommand(leg2_foot, 1500, 1000, 0);
  moveMotorCommand(leg3_foot, 1500, 1000, 0);
  moveMotorCommand(leg4_foot, 1500, 1000, 0);
  moveMotorCommand(leg5_foot, 1500, 1000, 0);
  moveMotorCommand(leg6_foot, 1500, 1000, 0);
  
  commitMoveMotorCommands();
  delay(3000);
}

//Function to transmit Commands from ESP32 to Motor Driver over Serial
  // ch = channel, pw = pulse width, spd = movement speed in microseconds per second,
  // tm = time (microsec) to travel from current position to the desired position
  // for single motor move choose either spd or tm
  // for multi motor move choose either spd or tm for each motor
  // do not forget to send a carriage return ("<cr") to execute movements
void moveMotorCommand(int ch, int pw, int spd, int tm){

  int body_pw_min = 1200;
  int body_pw_max = 1750;
  
  if ((spd != 0) && (tm != 0)){
    return;
  }

  if ((pw < body_pw_min) || (pw > body_pw_max)){
    return;
  }
  
  Serial.print("#");
  Serial.print(ch);
  Serial.print("P");
  
  Serial.print(pw);

  if (spd != 0){
    Serial.print("S");
    Serial.print(spd);
  }
  if (tm != 0){
    Serial.print("T");
    Serial.print(tm);
  }
}

// Function to "commit/execute" all motor commands sent since last carriage return ("<cr>")
void commitMoveMotorCommands (){
  Serial.println("<cr>");
}



void loop() {
  delay(2000);
  //move Group A Legs up
  moveMotorCommand(leg1_middle, 1500, 1000, 0);
  moveMotorCommand(leg3_middle, 1500, 1000, 0);
  //moveMotorCommand(leg3_foot, 1500, 1000, 0);
  moveMotorCommand(leg5_middle, 1500, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);

  //move Group A Legs forward
  moveMotorCommand(leg1_body, 1650, 1000, 0);
  moveMotorCommand(leg3_body, 1650, 1000, 0);
  moveMotorCommand(leg5_body, 1350, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);

  //move Group B Legs backward
  moveMotorCommand(leg2_body, 1500, 1000, 0);
  moveMotorCommand(leg4_body, 1500, 1000, 0);
  moveMotorCommand(leg4_foot, 1350, 1000, 0);
  moveMotorCommand(leg6_body, 1500, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);

  //move Group A Legs down
  moveMotorCommand(leg1_middle, 1700, 1000, 0);
  moveMotorCommand(leg3_middle, 1700, 1000, 0);
  moveMotorCommand(leg5_middle, 1700, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);


  //move Group B Legs up
  moveMotorCommand(leg2_middle, 1500, 1000, 0);
  moveMotorCommand(leg4_middle, 1500, 1000, 0);
  //moveMotorCommand(leg4_foot, 1500, 1000, 0);
  moveMotorCommand(leg6_middle, 1500, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);
  
  //move Group B Legs forward
  moveMotorCommand(leg2_body, 1650, 1000, 0);
  moveMotorCommand(leg4_body, 1350, 1000, 0);
  moveMotorCommand(leg6_body, 1350, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);

  //move Group A Legs backward
  moveMotorCommand(leg1_body, 1500, 1000, 0);
  moveMotorCommand(leg3_body, 1500, 1000, 0);
  //moveMotorCommand(leg3_foot, 1350, 1000, 0);
  moveMotorCommand(leg5_body, 1500, 1000, 0);
  commitMoveMotorCommands();
  delay(2000);

  //move Group B Legs down
  moveMotorCommand(leg2_middle, 1700, 1000, 0);
  moveMotorCommand(leg4_middle, 1700, 1000, 0);
  moveMotorCommand(leg6_middle, 1700, 1000, 0);
  commitMoveMotorCommands();
}
