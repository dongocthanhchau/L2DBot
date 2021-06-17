#include "car.h"
extern unsigned long t;
void moveMotor(int left, int right, bool dir){
  digitalWrite(right,dir);
  digitalWrite(left,!dir);
}
void stopMotor(int left, int right){
  digitalWrite(right, 0);
  digitalWrite(left, 0);
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
void turnRight(void){
  moveMotor(LA,RA,0);
  moveMotor(LB,RB,1);
  moveMotor(LC,RC,0);
  moveMotor(LD,RD,1);
}
void turnLeft(void){
  moveMotor(LA,RA,1);
  moveMotor(LB,RB,0);
  moveMotor(LC,RC,1);
  moveMotor(LD,RD,0);
}
void carControl(int cmnd){
  Serial.println(cmnd);
  t=millis()+1000;
  if (cmnd ==1){
    m1();
  }
  else if (cmnd==2){
    m2();
  }
  else if (cmnd==3){
    m3();
  }
  else if (cmnd==4){
    m4();
  }
  else if (cmnd==0){
    m5();
  }
  else if (cmnd==6){
    m6();
  }
  else if (cmnd==7){
    m7();
  }
  else if (cmnd==8){
    m8();
  }
  else if (cmnd==9){
    m9();
  }
  else if (cmnd==60){
	turnLeft();
	t -= 500;
  }
  else if (cmnd==66){
	turnRight();
	t -= 500;
  }
  else {
    stopAll();
    t=0;
  }
}