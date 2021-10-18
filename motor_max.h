//class and functions for representing motors
#ifndef MOTOR_MAX_H
#define MOTOR_MAX_H

#define MAX_SPEED 255
#define MIN_SPEED 0

class MotorM{
    private:
    uint8_t ahead_pin;
    uint8_t back_pin;
    uint8_t pwm_pin;

    public:
    MotorM(uint8_t ahead_pin, uint8_t back_pin, uint8_t pwm_pin);
    void setDir(bool isAhead);

    //range of speed: 0-255
    //speed exceeds range will be made 0 or 255
    //Arduino can only handle 8 bits PWM signal
    void setSpd(uint8_t speed);

    //range of speed: 0-255
    void setDirSpd(bool isAhead, uint8_t speed);

    void stopMotor();
};

#endif