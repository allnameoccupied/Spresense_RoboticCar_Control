//functions and classes by Max
#include "board_init_max.h"
#include "motor_max.h"
#include "motor_controller_max.h"
#include "util_max.h"
//for camera, tft LCD, SD card
#include <Camera.h>
#include <SPI.h>
#include <SDHCI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>
#include <Adafruit_ILI9341.h>


#define from_MAX 12345

//base definition of program behaviour
#define IS_USE_MOTOR true       //use motor == not use tft_LCD

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

//4 motors, initialized in setup()
static MotorM* top_left_motor = nullptr;
static MotorM* top_right_motor = nullptr;
static MotorM* bottom_left_motor = nullptr;
static MotorM* bottom_right_motor = nullptr;

//motor driver, initialized in setup()
static MotorControllerM* motor_controller = nullptr;

//TFT LCD, initialized in setup()
static Adafruit_ILI9341* TFT_LCD = nullptr;

//SD card, initialized in setup()
static SDClass SDcard;

//Camera, initialized in setup()
static CameraClass* Camera_Spresense = nullptr;


//MAIN PROGRAM
void setup() {
    //init Spresense
    LED_init_M();
    PIN_init_M(IS_USE_MOTOR,PWM_pins);
    PIN_init_M(IS_USE_MOTOR,DIR_pins);

    //init custom motor controller & program variables
    motor_controller = new MotorControllerM(TOP_LEFT_AHEAD, TOP_LEFT_BACK, TOP_LEFT_PWM,
                                            TOP_RIGHT_AHEAD, TOP_RIGHT_BACK, TOP_RIGHT_PWM,
                                            BOTTOM_LEFT_AHEAD, BOTTOM_LEFT_BACK, BOTTOM_LEFT_PWM,
                                            BOTTOM_RIGHT_AHEAD, BOTTOM_RIGHT_BACK, BOTTOM_RIGHT_PWM);                                            
    top_left_motor = motor_controller->get_top_left_motor();
    top_right_motor = motor_controller->get_top_right_motor();
    bottom_left_motor = motor_controller->get_bottom_left_motor();
    bottom_right_motor = motor_controller->get_bottom_right_motor();

    //init Serial communication
    SERIAL_init_M();

    //init SD card
    SDcard_init_M(&SDcard);

    //init TFT LCD, also init 4 pins for buttons
    TFT_LCD = TFTLCD_init_M(!IS_USE_MOTOR);

    //init Camera
    Camera_init_M(&Camera_Spresense);

    //FOR TESTING USE
    init_test();

    //init finished
    Serial.println("init finished");
    LED_flash_init();
}
void loop() {
    // demo motor function
    // motor_controller->demo(1500,MAX_SPEED);
    // delay(1000);
    // motor_controller->demo(1500,MAX_SPEED/3);
    // delay(3000);

    //FOR TESTING USE
    loop_test();

    //blinks LED to show that system is not hanging
    LED_toggle_loop();
}


//FUNCTION for easier testing in init() & loop()
void init_test(){
    
}
void loop_test(){
    
}


//SUPPLEMENTARY FUNCTION

//make sure system not hanging
void LED_toggle_loop(){
    LED_toggle_M(LED0);
    delay(100);
}
//show that init finished
void LED_flash_init() {
    LED_turnON_M(LED0);
    delay(100);
    LED_turnON_M(LED1);
    delay(100);
    LED_turnON_M(LED2);
    delay(100);
    LED_turnON_M(LED3);
    delay(1000);

    LED_turnOFF_M(LED0);
    delay(100);
    LED_turnOFF_M(LED1);
    delay(100);
    LED_turnOFF_M(LED2);
    delay(100);
    LED_turnOFF_M(LED3);
    delay(1000);
}