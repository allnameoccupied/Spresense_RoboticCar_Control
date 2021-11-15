//implementations of functions for initialization
#include "board_init_max.h"
#include "util_max.h"
// #include <pins_arduino.h>

void LED_init_M(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    is_LED_0_ON = false;
    is_LED_1_ON = false;
    is_LED_2_ON = false;
    is_LED_3_ON = false;
}

void PIN_init_M(const bool is_really_use, const uint8_t pin_array[]){
    if (!is_really_use){return;}
    PIN_init_M(pin_array);
}

void PIN_init_M(const uint8_t pin_array[]){
    for (uint8_t i = 0; i < sizeof pin_array / sizeof pin_array[0]; i++){
        PIN_init_M(*(pin_array+i));
    }
    
}

void PIN_init_M(const uint8_t pin){
    pinMode(pin, OUTPUT);
}

void SERIAL_init_M(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

Adafruit_ILI9341* TFTLCD_init_M(bool is_useTFTLCD){
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

void SDcard_init_M(SDClass* SDcard){
    SDcard->begin();
}

void Camera_init_M(CameraClass** camera){
    *camera = &theCamera;
    camera_util = &theCamera;
    theCamera.begin();
    theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_AUTO);
    is_camera_capturing = false;
}