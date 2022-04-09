//Written by MAX (Created 7-4-2022)

//implementation of a virtual motor controller 
//to better translate calculated input to actual motor input
#include "Motor_controller.h"

using namespace motor_controller_init_temp;

MotorController::MotorController(
    uint8_t top_left_ahead_pin, uint8_t top_left_back_pin, uint8_t top_left_pwm_pin, uint8_t top_left_hall_1_pin, uint8_t top_left_hall_2_pin,
    uint8_t top_right_ahead_pin, uint8_t top_right_back_pin, uint8_t top_right_pwm_pin, uint8_t top_right_hall_1_pin, uint8_t top_right_hall_2_pin,
    uint8_t bot_left_ahead_pin, uint8_t bot_left_back_pin, uint8_t bot_left_pwm_pin, uint8_t bot_left_hall_1_pin, uint8_t bot_left_hall_2_pin,
    uint8_t bot_right_ahead_pin, uint8_t bot_right_back_pin, uint8_t bot_right_pwm_pin, uint8_t bot_right_hall_1_pin, uint8_t bot_right_hall_2_pin)
    {
        this->global_max_speed = 0;
        this->curr_global_PWM_ratio_input = 0.0;
        
        this->Top_Left_Motor = new Motor(top_left_ahead_pin,top_left_back_pin,top_left_pwm_pin,top_left_hall_1_pin,top_left_hall_2_pin);
        this->is_Hall_Working_Top_Left_Motor = true;
        this->Top_Right_Motor = new Motor(top_right_ahead_pin,top_right_back_pin,top_right_pwm_pin,top_right_hall_1_pin,top_right_hall_2_pin);
        this->is_Hall_Working_Top_Right_Motor = true;
        this->Bot_Left_Motor = new Motor(bot_left_ahead_pin,bot_left_back_pin,bot_left_pwm_pin,bot_left_hall_1_pin,bot_left_hall_2_pin);
        this->is_Hall_Working_Bot_Left_Motor = true;
        this->Bot_Right_Motor = new Motor(bot_right_ahead_pin,bot_right_back_pin,bot_right_pwm_pin,bot_right_hall_1_pin,bot_right_hall_2_pin);
        this->is_Hall_Working_Bot_Right_Motor = true;
}

void MotorController::Motor_init(){
    //attach interrupt
    attachInterrupt(digitalPinToInterrupt(Top_Left_Motor->hall_sensor_1_pin),motor_controller_init_interrupt_handler_top_left,RISING);
    attachInterrupt(digitalPinToInterrupt(Top_Left_Motor->hall_sensor_2_pin),motor_controller_init_interrupt_handler_top_left_hall_2,RISING);
    attachInterrupt(digitalPinToInterrupt(Top_Right_Motor->hall_sensor_1_pin),motor_controller_init_interrupt_handler_top_right,RISING);
    attachInterrupt(digitalPinToInterrupt(Top_Right_Motor->hall_sensor_2_pin),motor_controller_init_interrupt_handler_top_right_hall_2,RISING);
    attachInterrupt(digitalPinToInterrupt(Bot_Left_Motor->hall_sensor_1_pin),motor_controller_init_interrupt_handler_bot_left,RISING);
    attachInterrupt(digitalPinToInterrupt(Bot_Left_Motor->hall_sensor_2_pin),motor_controller_init_interrupt_handler_bot_left_hall_2,RISING);
    attachInterrupt(digitalPinToInterrupt(Bot_Right_Motor->hall_sensor_1_pin),motor_controller_init_interrupt_handler_bot_right,RISING);
    attachInterrupt(digitalPinToInterrupt(Bot_Right_Motor->hall_sensor_2_pin),motor_controller_init_interrupt_handler_bot_right_hall_2,RISING);
    while(!is_all_motors_completed);
    detachInterrupt(digitalPinToInterrupt(Top_Left_Motor->hall_sensor_1_pin));
    detachInterrupt(digitalPinToInterrupt(Top_Left_Motor->hall_sensor_2_pin));
    detachInterrupt(digitalPinToInterrupt(Top_Right_Motor->hall_sensor_1_pin));
    detachInterrupt(digitalPinToInterrupt(Top_Right_Motor->hall_sensor_2_pin));
    detachInterrupt(digitalPinToInterrupt(Bot_Left_Motor->hall_sensor_1_pin));
    detachInterrupt(digitalPinToInterrupt(Bot_Left_Motor->hall_sensor_2_pin));
    detachInterrupt(digitalPinToInterrupt(Bot_Right_Motor->hall_sensor_1_pin));
    detachInterrupt(digitalPinToInterrupt(Bot_Right_Motor->hall_sensor_2_pin));
    
    Top_Left_Motor->abs_max_speed = top_left_top_spd;
    Top_Left_Motor->max_speed = top_left_spd_sum/MOTOR_INIT_ROTATION;
    Top_Right_Motor->abs_max_speed = top_right_top_spd;
    Top_Right_Motor->max_speed = top_right_spd_sum/MOTOR_INIT_ROTATION;
    Bot_Left_Motor->abs_max_speed = bot_left_top_spd;
    Bot_Left_Motor->max_speed = bot_left_spd_sum/MOTOR_INIT_ROTATION;
    Bot_Right_Motor->abs_max_speed = bot_right_top_spd;
    Bot_Right_Motor->max_speed = bot_right_spd_sum/MOTOR_INIT_ROTATION;
    
    global_max_speed = top_left_top_spd;
    if(top_right_top_spd < global_max_speed){
        global_max_speed = top_right_top_spd;
    }
    if (bot_left_top_spd < global_max_speed){
        global_max_speed = bot_left_top_spd;
    }
    if (bot_right_top_spd < global_max_speed){
        global_max_speed = bot_right_top_spd;
    }
    
    Top_Left_Motor->PWM_multiplier = Top_Left_Motor->max_speed/global_max_speed - 1.0;
    Top_Right_Motor->PWM_multiplier = Top_Right_Motor->max_speed/global_max_speed - 1.0;
    Bot_Left_Motor->PWM_multiplier = Bot_Left_Motor->max_speed/global_max_speed - 1.0;
    Bot_Right_Motor->PWM_multiplier = Bot_Right_Motor->max_speed/global_max_speed - 1.0;
}

void motor_controller_init_interrupt_handler_top_left(){
    if(top_left_curr_hall_1 == MOTOR_INIT_ROTATION){return;}
    if(top_left_curr_hall_1 == -1){    //start
        top_left_curr_hall_2 = -1;
        top_left_last_tick = millis();
    }
    if(top_left_curr_hall_1 > -1 &&    //during rotations
        top_left_curr_hall_1 < MOTOR_INIT_ROTATION){
        
        uint32_t curr_millis = millis();
        uint32_t curr_spd = curr_millis-top_left_last_tick;
        top_left_last_tick = curr_millis;
        if(curr_spd < top_left_top_spd || top_left_top_spd == 0){
            top_left_top_spd = curr_spd;
        }
        top_left_spd_sum += curr_spd;
    }
    top_left_curr_hall_1 += 1;
    if(top_left_curr_hall_1 == MOTOR_INIT_ROTATION){    //all rotations finished
        // top_left_avg_spd = top_left_spd_sum/MOTOR_INIT_ROTATION;
        if(top_right_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_left_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_right_curr_hall_1 == MOTOR_INIT_ROTATION){
               is_all_motors_completed == true;
        }
    }
}

void motor_controller_init_interrupt_handler_top_left_hall_2(){
    top_left_curr_hall_2 += 1;   
}

void motor_controller_init_interrupt_handler_top_right(){
    if(top_right_curr_hall_1 == MOTOR_INIT_ROTATION){return;}
    if(top_right_curr_hall_1 == -1){    //start
        top_right_curr_hall_2 = -1;
        top_right_last_tick = millis();
    }
    if(top_right_curr_hall_1 > -1 &&    //during rotations
        top_right_curr_hall_1 < MOTOR_INIT_ROTATION){
        
        uint32_t curr_millis = millis();
        uint32_t curr_spd = curr_millis-top_right_last_tick;
        top_right_last_tick = curr_millis;
        if(curr_spd < top_right_top_spd || top_right_top_spd == 0){
            top_right_top_spd = curr_spd;
        }
        top_right_spd_sum += curr_spd;
    }
    top_right_curr_hall_1 += 1;
    if(top_right_curr_hall_1 == MOTOR_INIT_ROTATION){    //all rotations finished
        // top_right_avg_spd = top_right_spd_sum/MOTOR_INIT_ROTATION;
        if(top_left_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_left_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_right_curr_hall_1 == MOTOR_INIT_ROTATION){
               is_all_motors_completed == true;
        }
    }
}

void motor_controller_init_interrupt_handler_top_right_hall_2(){
    top_right_curr_hall_2 += 1;
}

void motor_controller_init_interrupt_handler_bot_left(){
    if(bot_left_curr_hall_1 == MOTOR_INIT_ROTATION){return;}
    if(bot_left_curr_hall_1 == -1){    //start
        bot_left_curr_hall_2 = -1;
        bot_left_last_tick = millis();
    }
    if(bot_left_curr_hall_1 > -1 &&    //during rotations
        bot_left_curr_hall_1 < MOTOR_INIT_ROTATION){
        
        uint32_t curr_millis = millis();
        uint32_t curr_spd = curr_millis-bot_left_last_tick;
        bot_left_last_tick = curr_millis;
        if(curr_spd < bot_left_top_spd || bot_left_top_spd == 0){
            bot_left_top_spd = curr_spd;
        }
        bot_left_spd_sum += curr_spd;
    }
    bot_left_curr_hall_1 += 1;
    if(bot_left_curr_hall_1 == MOTOR_INIT_ROTATION){    //all rotations finished
        // bot_left_avg_spd = bot_left_spd_sum/MOTOR_INIT_ROTATION;
        if(top_left_curr_hall_1 == MOTOR_INIT_ROTATION &&
           top_right_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_right_curr_hall_1 == MOTOR_INIT_ROTATION){
               is_all_motors_completed == true;
        }
    }
}

void motor_controller_init_interrupt_handler_bot_left_hall_2(){
    bot_left_curr_hall_2 += 1;
}

void motor_controller_init_interrupt_handler_bot_right(){
    if(bot_right_curr_hall_1 == MOTOR_INIT_ROTATION){return;}
    if(bot_right_curr_hall_1 == -1){    //start
        bot_right_curr_hall_2 = -1;
        bot_right_last_tick = millis();
    }
    if(bot_right_curr_hall_1 > -1 &&    //during rotations
        bot_right_curr_hall_1 < MOTOR_INIT_ROTATION){
        
        uint32_t curr_millis = millis();
        uint32_t curr_spd = curr_millis-bot_right_last_tick;
        bot_right_last_tick = curr_millis;
        if(curr_spd < bot_right_top_spd || bot_right_top_spd == 0){
            bot_right_top_spd = curr_spd;
        }
        bot_right_spd_sum += curr_spd;
    }
    bot_right_curr_hall_1 += 1;
    if(bot_right_curr_hall_1 == MOTOR_INIT_ROTATION){    //all rotations finished
        // bot_right_avg_spd = bot_right_spd_sum/MOTOR_INIT_ROTATION;
        if(top_left_curr_hall_1 == MOTOR_INIT_ROTATION &&
           top_right_curr_hall_1 == MOTOR_INIT_ROTATION &&
           bot_left_curr_hall_1 == MOTOR_INIT_ROTATION){
               is_all_motors_completed == true;
        }
    }
}

void motor_controller_init_interrupt_handler_bot_right_hall_2(){
    bot_right_curr_hall_2 += 1;
}