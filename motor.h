#ifndef _MOTOR_H
#define	_MOTOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000
volatile struct DC_motor motorL, motorR;
volatile char TurningSpeed = 75;

struct DC_motor {
    char power; //motor power, out of 100
    char direction; //motor direction, forward(1), reverse(0)
    unsigned char *dutyLowByte; //PWM duty low byte address
    unsigned char *dutyHighByte; //PWM duty high byte address
    char dir_pin; // pin that controls direction on PORTB
    int PWMperiod; //base period of PWM cycle
}; //struct motor

void initMotor();
void setMotorPWM(struct DC_motor *m);
void stop(struct DC_motor *m_L, struct DC_motor *m_R);
void turnLeft(struct DC_motor *m_L, struct DC_motor *m_R);
void turnRight(struct DC_motor *m_L, struct DC_motor *m_R);
void fullSpeedAhead(struct DC_motor *m_L, struct DC_motor *m_R);
void setMotorFullSpeed(struct DC_motor *m);
void delay_s(int seconds);

#endif	/* XC_HEADER_TEMPLATE_H */

