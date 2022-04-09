//Written by MAX (Created 7-4-2022)

//class and functions representing a motor
#ifndef MOTOR_H
#define MOTOR_H

//PWM range
#define MAX_PWM 255
#define MIN_PWM 0

class Motor{
    public:
    
    //true == forward, false == backward
    bool curr_DIR;
    uint8_t curr_PWM;

    uint8_t ahead_pin;
    uint8_t back_pin;
    uint8_t pwm_pin;
    uint8_t hall_sensor_1_pin;
    uint8_t hall_sensor_2_pin;

    //lowest speed (millis per full_wheel_rotation) with full PWM during init
    uint32_t abs_max_speed;
    //average speed (millis per full_wheel_rotation) with full PWM during init
    uint32_t max_speed;
    //modifier for catching up to faster motor in same robot
    float PWM_multiplier;
    
    Motor(uint8_t ahead_pin, uint8_t back_pin, uint8_t pwm_pin,
            uint8_t hall_sensor_1_pin, uint8_t hall_sensor_2_pin);
    
    void setDir(bool dir);

    //range of PWM: 0-255
    //PWM exceeds range will be made 0 or 255
    //Arduino can only handle 8 bits PWM signal
    void setPwm(uint8_t pwm);

    //range of PWM: 0-255
    void setDirPwm(bool dir, uint8_t pwm);

    void stopMotor();
};

#endif