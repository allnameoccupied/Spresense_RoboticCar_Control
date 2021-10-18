// implementation of the custom motor class
#include "motor_max.h"

MotorM::MotorM(uint8_t ahead_pin, uint8_t back_pin, uint8_t pwm_pin){
    this->ahead_pin = ahead_pin;
    this->back_pin = back_pin;
    this->pwm_pin = pwm_pin;
}

void MotorM::setDir(bool isAhead){
    if (isAhead)
    {
        digitalWrite(ahead_pin, HIGH);
        digitalWrite(back_pin, LOW);
    }
    else
    {
        digitalWrite(ahead_pin, LOW);
        digitalWrite(back_pin, HIGH);
    }
    
}

void MotorM::setSpd(uint8_t speed){
    if (speed<MIN_SPEED){
        speed=MIN_SPEED;
    }
    if (speed>MAX_SPEED){
        speed=MAX_SPEED;
    }
    analogWrite(pwm_pin,speed);
}

void MotorM::setDirSpd(bool isAhead, uint8_t speed){
    setDir(isAhead);
    setSpd(speed);
}

void MotorM::stopMotor(){
    digitalWrite(ahead_pin, LOW);
    digitalWrite(back_pin, LOW);
    analogWrite(pwm_pin,MIN_SPEED);
}