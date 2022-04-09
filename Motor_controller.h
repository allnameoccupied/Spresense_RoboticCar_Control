//Written by MAX (Created 7-4-2022)

//a virtual motor controller 
//to better translate calculated input to actual motor input
#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

//PWM range
#define MAX_PWM 255
#define MIN_PWM 0

//Motor specification
//according to https://www.amazon.com/OSOYOO-Robotic-Mecanum-Platform-Raspberry/dp/B07WZJYVB5
#define RATED_V     9 //V
//C = circumference
#define WHEEL_C     80*PI //mm  //~251mm
#define GEAR_RATIO  75 //1:75
#define MOTOR_SPEED 11500 //rpm

//Some definitions
//Unit of speed = millis per full_wheel_rotation  (transformable to mm per millis)
//Unit of coordinate plane unit = 20 mm
//global = apply to 4 motors
#define DEFAULT_DUTY_RATIO      0.5
#define COOR_PLANE_UNIT_LENGTH  20 //mm

//Motor init settings
#define MOTOR_INIT_ROTATION     10

class MotorController{
    public:

    //lowest average speed with full PWM among 4 motors during init
    uint32_t global_max_speed;
    float curr_global_PWM_ratio_input;

    Motor* Top_Left_Motor;
    bool is_Hall_Working_Top_Left_Motor;
    Motor* Top_Right_Motor;
    bool is_Hall_Working_Top_Right_Motor;
    Motor* Bot_Left_Motor;
    bool is_Hall_Working_Bot_Left_Motor;
    Motor* Bot_Right_Motor;
    bool is_Hall_Working_Bot_Right_Motor;
    
    MotorController(
        uint8_t top_left_ahead_pin, uint8_t top_left_back_pin, uint8_t top_left_pwm_pin, uint8_t top_left_hall_1_pin, uint8_t top_left_hall_2_pin,
        uint8_t top_right_ahead_pin, uint8_t top_right_back_pin, uint8_t top_right_pwm_pin, uint8_t top_right_hall_1_pin, uint8_t top_right_hall_2_pin,
        uint8_t bot_left_ahead_pin, uint8_t bot_left_back_pin, uint8_t bot_left_pwm_pin, uint8_t bot_left_hall_1_pin, uint8_t bot_left_hall_2_pin,
        uint8_t bot_right_ahead_pin, uint8_t bot_right_back_pin, uint8_t bot_right_pwm_pin, uint8_t bot_right_hall_1_pin, uint8_t bot_right_hall_2_pin);

    void Motor_init();

    //TODO func to take care of PWM multiplier
    //TODO determine what type of input to take
};

namespace motor_controller_init_temp{
    static bool is_all_motors_completed = false;

    static uint32_t top_left_last_tick = 0;
    static uint32_t top_left_top_spd = 0;
    static uint32_t top_left_spd_sum = 0;
    // static uint32_t top_left_avg_spd = 0;
    static int      top_left_curr_hall_1 = -1;
    static int      top_left_curr_hall_2 = -1;
    // static uint32_t top_left_spd[MOTOR_INIT_ROTATION];
    static uint32_t top_right_last_tick = 0;
    static uint32_t top_right_top_spd = 0;
    static uint32_t top_right_spd_sum = 0;
    // static uint32_t top_right_avg_spd = 0;
    static int      top_right_curr_hall_1 = -1;
    static int      top_right_curr_hall_2 = -1;
    // static uint32_t top_right_spd[MOTOR_INIT_ROTATION];
    static uint32_t bot_left_last_tick = 0;
    static uint32_t bot_left_top_spd = 0;
    static uint32_t bot_left_spd_sum = 0;
    // static uint32_t bot_left_avg_spd = 0;
    static int      bot_left_curr_hall_1 = -1;
    static int      bot_left_curr_hall_2 = -1;
    // static uint32_t bot_left_spd[MOTOR_INIT_ROTATION];
    static uint32_t bot_right_last_tick = 0;
    static uint32_t bot_right_top_spd = 0;
    static uint32_t bot_right_spd_sum = 0;
    // static uint32_t bot_right_avg_spd = 0;
    static int      bot_right_curr_hall_1 = -1;
    static int      bot_right_curr_hall_2 = -1;
    // static uint32_t bot_right_spd[MOTOR_INIT_ROTATION];
}

#endif