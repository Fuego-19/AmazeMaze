#include <Servo.h>

Servo rightMotor, leftMotor, upMotor, downMotor;

float in_val = 0.0f;
int count = 0;
float cur_val = 0.0f;
int rnum = 0;
boolean flag = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), magnet_detect, CHANGE);  //Initialize the intterrupt pin (Arduino digital pin 2)
  attachInterrupt(digitalPinToInterrupt(3), magnet_detect1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), magnet_detect2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), magnet_detect3, CHANGE);
  rightMotor.attach(13);
  leftMotor.attach(12);
  upMotor.attach(11);
  downMotor.attach(10);
  rightMotor.write(90);
  leftMotor.write(90);
  upMotor.write(90);
  downMotor.write(90);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag){ 
    offLed();
    randGen();
    glowLed();
  }
  
  if (Serial.available() > 0){
    count = 0;
    in_val = Serial.read();
//    Serial.println(in_val);
    if (cur_val != in_val) {
      if (in_val == 49) {         // up
        cur_val = in_val;
//        Serial.println("UP");
        tiltUp();
      }
      else if (in_val == 50) {    // down
        cur_val = in_val;
//        Serial.println("D");
        tiltDown();
      }
      else if (in_val == 51) {    // right
        cur_val = in_val;
//        Serial.println("R");
        tiltRight();
      }
      else if (in_val == 52) {    // left
        cur_val = in_val;
//        Serial.println("L");
        tiltLeft();
      }
    }
  }
  else {
    count++;
    delay(30);
  }
  if (count >= 8) {
    if (cur_val != 0){
//      Serial.println("Stable");
      stableMotor();
      cur_val = 0;
    }
    count = 0;
  }
}

void stableMotor() {
  rightMotor.write(90);
  leftMotor.write(90);
  upMotor.write(90);
  downMotor.write(90);
//  Serial.println("Motor Stable");
  delay(50);
}

void tiltRight() {
  stableMotor();
  rightMotor.write(135);
  leftMotor.write(45);
  upMotor.write(180);
  downMotor.write(90);
//  Serial.println("Motor Right");
  delay(50);
}

void tiltLeft() {
  stableMotor();
  rightMotor.write(45);
  leftMotor.write(135);
  upMotor.write(90);
  downMotor.write(180);
//  Serial.println("Motor Left");
  delay(50);
}

void tiltUp() {
  stableMotor();
  rightMotor.write(180);
  leftMotor.write(90);
  upMotor.write(135);
  downMotor.write(45);
//  Serial.println("Motor Up");
  delay(50);
}

void tiltDown() {
  stableMotor();
  rightMotor.write(90);
  leftMotor.write(180);
  upMotor.write(45);
  downMotor.write(135);
//  Serial.println("Motor Down");
  delay(50);
}

void magnet_detect(){
  if(rnum == 4){
    Serial.println("detected");
    flag = true;
  }
}

void magnet_detect1()
{
  if(rnum == 5){
    Serial.println("detected");
    flag = true;
  }
}

void magnet_detect2(){
  if(rnum == 6){
    Serial.println("detected");
    flag = true;
  }
}

void magnet_detect3(){
  if(rnum == 7){
    Serial.println("detected");
    flag = true;
  }
}

void glowLed(){
  digitalWrite(rnum , HIGH);
  Serial.println(rnum);
  flag = false;
}

void offLed(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
void randGen(){
  while(true){
//    long temp = (rand()%4) + 4;
    long temp = random(4,8);
    if(temp != rnum){
      rnum = temp;
      break;
    }
  }
}
