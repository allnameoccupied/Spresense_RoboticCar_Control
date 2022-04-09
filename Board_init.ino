//Written by MAX (Created 7-4-2022)

//implementations of functions for initialization
#include "Board_init.h"
#include "LED.h"
#include "Spresense_Camera.h"
// #include <pins_arduino.h>

void LED_init(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    is_LED_0_ON = false;
    is_LED_1_ON = false;
    is_LED_2_ON = false;
    is_LED_3_ON = false;
}

void PIN_init_array(const uint8_t pin_array[], const Pin_type pin_type_array[]){
    if (sizeof pin_array/sizeof pin_array[0] != sizeof pin_type_array/sizeof pin_type_array[0]){
        return;
    }
    for (uint8_t i = 0; i < sizeof pin_array / sizeof pin_array[0]; i++){
        // PIN_init(pin_array[i], pin_type_array[i]);
        pinMode(pin_array[i], pin_type_array[i]);
    }
    delete pin_type_array;
}

void PIN_init_motor(const bool is_use_motor, const uint8_t PWM_pin_array[], const uint8_t DIR_pin_array[], const uint8_t HALL_pin_array[]){
    if (!is_use_motor){return;}    
    for (uint8_t i = 0; i < sizeof PWM_pin_array / sizeof PWM_pin_array[0]; i++){
        pinMode(PWM_pin_array[i], OUTPUT);
    }
    for (uint8_t i = 0; i < sizeof DIR_pin_array / sizeof DIR_pin_array[0]; i++){
        pinMode(DIR_pin_array[i], OUTPUT);
    }
    for (uint8_t i = 0; i < sizeof HALL_pin_array / sizeof HALL_pin_array[0]; i++){
        pinMode(HALL_pin_array[i], INPUT_PULLDOWN);
    }
}

void SERIAL_init(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

Adafruit_ILI9341* TFTLCD_init(bool is_useTFTLCD){
    if (!is_useTFTLCD){return nullptr;}
    pinMode(PIN_D04, INPUT_PULLUP);
    pinMode(PIN_D05, INPUT_PULLUP);
    pinMode(PIN_D06, INPUT_PULLUP);
    pinMode(PIN_D07, INPUT_PULLUP);
    Adafruit_ILI9341* temp_tft = new Adafruit_ILI9341(&SPI,TFT_DC,TFT_CS,TFT_RST);
    temp_tft->begin();
    // temp_tft->setRotation(0);
    return temp_tft;
}

void SDcard_init(SDClass* SDcard){
    SDcard->begin();
}

void Camera_init(CameraClass** camera){
    *camera = &theCamera;
    camera_util = &theCamera;
    theCamera.begin();
    theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_AUTO);
    is_camera_capturing = false;
}