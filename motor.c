#include <xc.h>
#include "motor.h"

void initMotor() {
    int PWMcycle = 199;
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    PTCON0 = 0b00000000; // free running mode, 1:1 prescaler
    PTCON1 = 0b10000000; // enable PWM timer
    PWMCON0 = 0b01101111; // PWM1/3 enabled, all independent mode
    PWMCON1 = 0x00; // special features, all 0 (default)
    PTPERL = 0b11000111; // base PWM period low byte
    PTPERH = 0b00000000; // base PWM period high byte 
    PDC0L = 0b00000000;
    PDC0H = 0b00000000;
    PDC1L = 0b00000000;
    PDC1H = 0b00000000;

    motorL.power = 0; //zero power to start
    motorL.direction = 1; //set default motor direction
    motorL.dutyLowByte = (unsigned char *) (&PDC0L); //store address of PWM duty low byte
    motorL.dutyHighByte = (unsigned char *) (&PDC0H); //store address of PWM duty high byte
    motorL.dir_pin = 0; //pin RB0/PWM0 controls direction
    motorL.PWMperiod = PWMcycle; //store PWMperiod for motor

    //same for motorR but different PWM registers and direction pin
    motorR.power = 0; //zero power to start
    motorR.direction = 1; //set default motor direction
    motorR.dutyLowByte = (unsigned char *) (&PDC1L); //store address of PWM duty low byte
    motorR.dutyHighByte = (unsigned char *) (&PDC1H); //store address of PWM duty high byte
    motorR.dir_pin = 2; //pin RB2/PWM2 controls direction
    motorR.PWMperiod = PWMcycle; //store PWMperiod for motor
}

void setMotorPWM(struct DC_motor *m) {
    int PWMduty; //tmp variable to store PWM duty cycle
    if (m->direction) { //if forward
        // low time increases with power
        PWMduty = m->PWMperiod - ((int) (m->power)*(m->PWMperiod)) / 100;
    } else { //if reverse
        // high time increases with power
        PWMduty = ((int) (m->power)*(m->PWMperiod)) / 100;
    }
    PWMduty = (PWMduty << 2); // two LSBs are reserved for other things
    *(m->dutyLowByte) = PWMduty & 0xFF; //set low duty cycle byte
    *(m->dutyHighByte) = (PWMduty >> 8) & 0x3F; //set high duty cycle byte

    if (m->direction) { // if direction is high,
        LATB = LATB | (1 << (m->dir_pin)); // set dir_pin bit in LATB to high
    } else { // if direction is low,
        LATB = LATB & (~(1 << (m->dir_pin))); // set dir_pin bit in LATB to low
    }
}

void stop(struct DC_motor *m_L, struct DC_motor *m_R) {
    motorR.power = 0;
    motorL.power = 0;
    setMotorPWM(&motorR);
    setMotorPWM(&motorL);
}

// turn robot base left on the spot

void turnLeft(struct DC_motor *m_L, struct DC_motor *m_R) {
    motorL.direction = 1;
    motorR.direction = 0;
    motorL.power = TurningSpeed;
    motorR.power = TurningSpeed;
    setMotorPWM(&motorR);
    setMotorPWM(&motorL);
}
// turn robot base right on the spot

void turnRight(struct DC_motor *m_L, struct DC_motor *m_R) {
    motorR.direction = 1;
    motorL.direction = 0;
    motorR.power = TurningSpeed;
    motorL.power = TurningSpeed;
    setMotorPWM(&motorR);
    setMotorPWM(&motorL);
}
// both motors forward and up to full power

void fullSpeedAhead(struct DC_motor *m_L, struct DC_motor *m_R) {
    motorR.direction = 1;
    motorL.direction = 1;
    motorL.power = TurningSpeed;
    motorR.power = TurningSpeed;
    setMotorPWM(&motorR);
    setMotorPWM(&motorL);

}

void setMotorFullSpeed(struct DC_motor *m) {
    for (m->power; (m->power) <= 100; (m->power)++) { //increase motor power until 100
        setMotorPWM(m); //pass pointer to setMotorSpeed function (not &m here)
        __delay_ms(5); //delay of 5 ms (500 ms from 0 to 100 full power)
    }
}

void delay_s(int seconds) {// function to delay in seconds
    unsigned int i;
    i = seconds * 20;
    unsigned int j;
    for (j = 0; j < i; j++) {
        __delay_ms(50);
    }
}

