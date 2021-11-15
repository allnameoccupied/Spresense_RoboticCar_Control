//functions for initializations of Spresense
#ifndef BOARD_INIT_MAX_H
#define BOARD_INIT_MAX_H

#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <SDHCI.h>
#include <Camera.h>

#define DEFAULT_BAUD_RATE 115200
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10

void LED_init_M();
void PIN_init_M(const bool is_really_use, const uint8_t pin_array[]);
void PIN_init_M(const uint8_t pin_array[]);
void PIN_init_M(const uint8_t pin);
void SERIAL_init_M();
Adafruit_ILI9341* TFTLCD_init_M(bool is_useTFTLCD);
void SDcard_init_M(SDClass* SDcard);
void Camera_init_M(CameraClass** camera);

#endif