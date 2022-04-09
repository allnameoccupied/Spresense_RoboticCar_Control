//Written by MAX (Created 7-4-2022)

//functions for initialization of Spresense
#ifndef BOARD_INIT_H
#define BOARD_INIT_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <SDHCI.h>
#include <Camera.h>

#define DEFAULT_BAUD_RATE 115200

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10

enum Pin_type{
    Input = INPUT,
    Output = OUTPUT,
    Input_Pullup = INPUT_PULLUP,
    Input_Pulldown = INPUT_PULLDOWN
};

void LED_init();
void PIN_init_array(const uint8_t pin_array[], const Pin_type pin_type_array[]);
void PIN_init_motor(const bool is_use_motor, const uint8_t PWM_pin_array[], const uint8_t DIR_pin_array[], const uint8_t HALL_pin_array[]);
void SERIAL_init();
Adafruit_ILI9341* TFTLCD_init(bool is_useTFTLCD);
void SDcard_init(SDClass* SDcard);
void Camera_init(CameraClass** camera);

#endif