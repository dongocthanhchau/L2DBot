#ifndef __car_h__
#define __car_h__

#include <Arduino.h>
#define RA 33
#define LA 32

#define RB 18
#define LB 5

#define RC 26
#define LC 25

#define RD 21
#define LD 19

void motorInit(void);
void stopAll(void);
void m1(void);
void m2(void);
void m3(void);
void m4(void);
void m5(void);
void m6(void);
void m7(void);
void m8(void);
void m9(void);
void turnLeft(void);
void turnRight(void);
void carControl(int cmnd);
#endif
