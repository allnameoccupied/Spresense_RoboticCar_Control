//Written by MAX (Created 7-4-2022)

// implementation of the custom motor class
#include "Motor.h"

Motor::Motor(uint8_t ahead_pin, uint8_t back_pin, uint8_t pwm_pin,
            uint8_t hall_sensor_1_pin, uint8_t hall_sensor_2_pin){
    this->curr_DIR = true;
    this->curr_PWM = MIN_PWM;
    
    this->ahead_pin = ahead_pin;
    this->back_pin = back_pin;
    this->pwm_pin = pwm_pin;
    this->hall_sensor_1_pin = hall_sensor_1_pin;
    this->hall_sensor_2_pin = hall_sensor_2_pin;

    this->abs_max_speed = 0;
    this->max_speed = 0;
    this->PWM_multiplier = 0.0;
}

void Motor::setDir(bool dir){
    curr_DIR = dir;
    if (dir){
        digitalWrite(ahead_pin, HIGH);
        digitalWrite(back_pin, LOW);
    } else {
        digitalWrite(ahead_pin, LOW);
        digitalWrite(back_pin, HIGH);
    }
}

void Motor::setPwm(uint8_t pwm){
    if (pwm<MIN_PWM){pwm=MIN_PWM;}
    if (pwm>MAX_PWM){pwm=MAX_PWM;}
    curr_PWM = pwm;
    analogWrite(pwm_pin,pwm);
}

void Motor::setDirPwm(bool dir, uint8_t pwm){
    setDir(dir);
    setPwm(pwm);
}

void Motor::stopMotor(){
    // digitalWrite(ahead_pin, LOW);
    // digitalWrite(back_pin, LOW);
    setPwm(MIN_PWM);
}