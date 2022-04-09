// //implementation of the custom motor controller class
// #include"motor_controller_max.h"

// MotorControllerM::MotorControllerM(
//         uint8_t top_left_ahead_pin, uint8_t top_left_back_pin, uint8_t top_left_pwm_pin,
//         uint8_t top_right_ahead_pin, uint8_t top_right_back_pin, uint8_t top_right_pwm_pin,
//         uint8_t bottom_left_ahead_pin, uint8_t bottom_left_back_pin, uint8_t bottom_left_pwm_pin,
//         uint8_t bottom_right_ahead_pin, uint8_t bottom_right_back_pin, uint8_t bottom_right_pwm_pin)
// {
//     top_left_motor = new MotorM(top_left_ahead_pin, top_left_back_pin, top_left_pwm_pin);
//     top_right_motor = new MotorM(top_right_ahead_pin, top_right_back_pin, top_right_pwm_pin);
//     bottom_left_motor = new MotorM(bottom_left_ahead_pin, bottom_left_back_pin, bottom_left_pwm_pin);
//     bottom_right_motor = new MotorM(bottom_right_ahead_pin, bottom_right_back_pin, bottom_right_pwm_pin);
// }

// MotorM* MotorControllerM::get_top_left_motor(){return top_left_motor;}
// MotorM* MotorControllerM::get_top_right_motor(){return top_right_motor;}
// MotorM* MotorControllerM::get_bottom_left_motor(){return bottom_left_motor;}
// MotorM* MotorControllerM::get_bottom_right_motor(){return bottom_right_motor;}

// void MotorControllerM::left_action(bool isAhead, uint8_t speed){
//     top_left_motor->setDirSpd(isAhead,speed);
//     bottom_left_motor->setDirSpd(isAhead,speed);
// }
// void MotorControllerM::right_action(bool isAhead, uint8_t speed){
//     top_right_motor->setDirSpd(isAhead,speed);
//     bottom_right_motor->setDirSpd(isAhead,speed);
// }

// void MotorControllerM::move(
//         bool isLeftAhead, uint8_t left_speed,
//         bool isRightAhead, uint8_t right_speed)
// {
//     left_action(isLeftAhead,left_speed);
//     right_action(isRightAhead,right_speed);
// }


// void MotorControllerM::move_ahead(uint8_t speed){
//     move(true,speed,true,speed);
// }
// void MotorControllerM::move_ahead(){
//     move_ahead(MAX_SPEED);
// }


// void MotorControllerM::move_back(uint8_t speed){
//     move(false,speed,false,speed);
// }
// void MotorControllerM::move_back(){
//     move_back(MAX_SPEED);
// }


// void MotorControllerM::turn_left_ahead(uint8_t speed){
//     move(true,MIN_SPEED,true,speed);
// }
// void MotorControllerM::turn_left_ahead(){
//     turn_left_ahead(MAX_SPEED);
// }


// void MotorControllerM::turn_left_back(uint8_t speed){
//     move(true,MIN_SPEED,false,speed);
// }
// void MotorControllerM::turn_left_back(){
//     turn_left_back(MAX_SPEED);
// }


// void MotorControllerM::turn_right_ahead(uint8_t speed){
//     move(true,speed,true,MIN_SPEED);
// }
// void MotorControllerM::turn_right_ahead(){
//     turn_right_ahead(MAX_SPEED);
// }


// void MotorControllerM::turn_right_back(uint8_t speed){
//     move(false,speed,true,MIN_SPEED);
// }
// void MotorControllerM::turn_right_back(){
//     turn_right_back(MAX_SPEED);
// }


// void MotorControllerM::rotate_clock(uint8_t speed){
//     move(true,speed,false,speed);
// }
// void MotorControllerM::rotate_clock(){
//     rotate_clock(MAX_SPEED);
// }


// void MotorControllerM::rotate_anticlock(uint8_t speed){
//     move(false,speed,true,speed);
// }
// void MotorControllerM::rotate_anticlock(){
//     rotate_anticlock(MAX_SPEED);
// }


// void MotorControllerM::stop(){
//     top_left_motor->stopMotor();
//     top_right_motor->stopMotor();
//     bottom_left_motor->stopMotor();
//     bottom_right_motor->stopMotor();
// }

// void MotorControllerM::demo(uint16_t action_duration, uint8_t speed){
//     move_ahead(speed);
//     delay(action_duration);
//     move_back(speed);
//     delay(action_duration);
//     turn_left_ahead(speed);
//     delay(action_duration);
//     turn_left_back(speed);
//     delay(action_duration);
//     turn_right_ahead(speed);
//     delay(action_duration);
//     turn_right_back(speed);
//     delay(action_duration);
//     rotate_clock(speed);
//     delay(action_duration);
//     rotate_anticlock(speed);
//     delay(action_duration);
//     stop();
//     delay(action_duration/2);
// }
// void MotorControllerM::demo(uint16_t action_duration){
//     demo(action_duration,MAX_SPEED);
// }