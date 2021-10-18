//definition of a controller for better controlling the 4 motors
#ifndef MOTOR_CONTROLLER_MAX_H
#define MOTOR_CONTROLLER_MAX_H

#include"motor_max.h"

#define MAX_SPEED 255
#define MIN_SPEED 0

class MotorControllerM{
    private:
    MotorM* top_left_motor;
    MotorM* top_right_motor;
    MotorM* bottom_left_motor;
    MotorM* bottom_right_motor;

    public:
    MotorControllerM(uint8_t top_left_ahead_pin, uint8_t top_left_back_pin, uint8_t top_left_pwm_pin,
                     uint8_t top_right_ahead_pin, uint8_t top_right_back_pin, uint8_t top_right_pwm_pin,
                     uint8_t bottom_left_ahead_pin, uint8_t bottom_left_back_pin, uint8_t bottom_left_pwm_pin,
                     uint8_t bottom_right_ahead_pin, uint8_t bottom_right_back_pin, uint8_t bottom_right_pwm_pin);
    
    MotorM* get_top_left_motor();
    MotorM* get_top_right_motor();
    MotorM* get_bottom_left_motor();
    MotorM* get_bottom_right_motor();

    void left_action(bool isAhead, uint8_t speed);
    void right_action(bool isAhead, uint8_t speed);

    //move ahead -> isAhead=true
    //move back  -> isAhead=false
    //stop       -> speed=0
    void move(bool isLeftAhead, uint8_t left_speed,
              bool isRightAhead, uint8_t right_speed);

    void move_ahead(uint8_t speed);
    void move_ahead();

    void move_back(uint8_t speed);
    void move_back();

    void turn_left_ahead(uint8_t speed);
    void turn_left_ahead();

    void turn_left_back(uint8_t speed);
    void turn_left_back();

    void turn_right_ahead(uint8_t speed);
    void turn_right_ahead();

    void turn_right_back(uint8_t speed);
    void turn_right_back();

    void rotate_clock(uint8_t speed);
    void rotate_clock();

    void rotate_anticlock(uint8_t speed);
    void rotate_anticlock();

    void stop();

    void demo(uint16_t action_duration, uint8_t speed);
    void demo(uint16_t action_duration);
};

#endif