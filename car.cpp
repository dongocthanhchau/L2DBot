#include "car.h"

void moveMotor(int left, int right, bool dir){
  digitalWrite(right,dir);
  digitalWrite(left,!dir);
  delay(1);
}
void stopMotor(int left, int right){
  digitalWrite(right, 0);
  digitalWrite(left, 0);
  delay(1);
}
void motorInit(void){
  pinMode(LA,OUTPUT);
  pinMode(RA,OUTPUT);
  pinMode(LB,OUTPUT);
  pinMode(RB,OUTPUT);
  pinMode(LC,OUTPUT);
  pinMode(RC,OUTPUT);
  pinMode(LD,OUTPUT);
  pinMode(RD,OUTPUT);
  stopAll();
}
void stopAll(void){
  stopMotor(LA,RA);
  stopMotor(LD,RD);
  stopMotor(LC,RC);
  stopMotor(LB,RB);
  Serial.println("STOP");
}
void m1(void){
  stopMotor(LA,RA);
  stopMotor(LD,RD);
  moveMotor(LB,RB,1);
  moveMotor(LC,RC,1);
}
void m3(void){
  stopMotor(LB,RB);
  stopMotor(LC,RC);
  moveMotor(LA,RA,1);
  moveMotor(LD,RD,1);
}
void m7(void){
  stopMotor(LB,RB);
  stopMotor(LC,RC);
  moveMotor(LA,RA,0);
  moveMotor(LD,RD,0);
}
void m9(void){
  stopMotor(LA,RA);
  stopMotor(LD,RD);
  moveMotor(LB,RB,0);
  moveMotor(LC,RC,0);
}

void m2(void){
  moveMotor(LA,RA,1);
  moveMotor(LB,RB,1);
  moveMotor(LC,RC,1);
  moveMotor(LD,RD,1);
}
void m4(void){
  moveMotor(LA,RA,0);
  moveMotor(LB,RB,1);
  moveMotor(LC,RC,1);
  moveMotor(LD,RD,0);
}
void m5(void){
  moveMotor(LA,RA,0);
  moveMotor(LB,RB,1);
  moveMotor(LC,RC,0);
  moveMotor(LD,RD,1);
}
void m6(void){
  moveMotor(LA,RA,1);
  moveMotor(LB,RB,0);
  moveMotor(LC,RC,0);
  moveMotor(LD,RD,1);
}
void m8(void){
  moveMotor(LA,RA,0);
  moveMotor(LB,RB,0);
  moveMotor(LC,RC,0);
  moveMotor(LD,RD,0);
}
