#include "board_init_max.h"
#include "motor_max.h"
#include "motor_controller_max.h"

#define from_MAX 12345

//PWM pin DEFINE
#define TOP_LEFT_PWM        PIN_D03
#define TOP_RIGHT_PWM       PIN_D05
#define BOTTOM_LEFT_PWM     PIN_D06
#define BOTTOM_RIGHT_PWM    PIN_D09
static const uint8_t PWM_pins[4] = {PIN_D06, PIN_D05, PIN_D09, PIN_D03};    //order of pin according to CXD5602 pwm pin order

//direction control pin DEFINE
#define TOP_LEFT_AHEAD      PIN_D02
#define TOP_LEFT_BACK       PIN_D04
#define TOP_RIGHT_AHEAD     PIN_D07
#define TOP_RIGHT_BACK      PIN_D08
#define BOTTOM_LEFT_AHEAD   PIN_D10
#define BOTTOM_LEFT_BACK    PIN_D11
#define BOTTOM_RIGHT_AHEAD  PIN_D12
#define BOTTOM_RIGHT_BACK   PIN_D13
static const uint8_t DIR_pins[8] = {PIN_D02, PIN_D04, PIN_D07, PIN_D08, PIN_D10, PIN_D11, PIN_D12, PIN_D13};

//4 motors, initialized below
static MotorM* top_left_motor = nullptr;
static MotorM* top_right_motor = nullptr;
static MotorM* bottom_left_motor = nullptr;
static MotorM* bottom_right_motor = nullptr;

//motor driver, initialized below
static MotorControllerM* motor_controller = nullptr;


//MAIN PROGRAM
void setup() {
    //init Spresense
    LED_init_max();
    PIN_init_max(PWM_pins);
    PIN_init_max(DIR_pins);

    //init custom controller & program variables
    motor_controller = new MotorControllerM(TOP_LEFT_AHEAD, TOP_LEFT_BACK, TOP_LEFT_PWM,
                                            TOP_RIGHT_AHEAD, TOP_RIGHT_BACK, TOP_RIGHT_PWM,
                                            BOTTOM_LEFT_AHEAD, BOTTOM_LEFT_BACK, BOTTOM_LEFT_PWM,
                                            BOTTOM_RIGHT_AHEAD, BOTTOM_RIGHT_BACK, BOTTOM_RIGHT_PWM);                                            
    top_left_motor = motor_controller->get_top_left_motor();
    top_right_motor = motor_controller->get_top_right_motor();
    bottom_left_motor = motor_controller->get_bottom_left_motor();
    bottom_right_motor = motor_controller->get_bottom_right_motor();

    //init finished
    LED_flash();
}

void loop() {
    //demo motor function
    motor_controller->demo(1500,MAX_SPEED);
    delay(1000);
    motor_controller->demo(1500,MAX_SPEED/3);
    delay(3000);

    //blinks LED to show that system is not hanging
    LED_toggle();
}

//SUPPLEMENTARY FUNCTION

//make sure system not hanging
void LED_toggle(){
    static bool led_toggle_state = true;
    if (led_toggle_state)
    {
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, LOW);
        led_toggle_state = false;
    }
    else
    {
        digitalWrite(LED0, LOW);
        digitalWrite(LED1, HIGH);
        led_toggle_state = true;
    }
}

void LED_flash() {
    digitalWrite(LED0, HIGH);
    delay(100);
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(1000);

    digitalWrite(LED0, LOW);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
    digitalWrite(LED2, LOW);
    delay(100);
    digitalWrite(LED3, LOW);
    delay(1000);
}