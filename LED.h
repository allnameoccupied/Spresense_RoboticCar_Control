//Written by MAX (Created 7-4-2022)

//functions to control LED on Spresense
#ifndef LED_H
#define LED_H

// ON/OFF state of each LED
static bool is_LED_0_ON;
static bool is_LED_1_ON;
static bool is_LED_2_ON;
static bool is_LED_3_ON;

// turn on one LED
// only work with LED0,1,2,3
void LED_ON(uint8_t LEDX);

// turn off one LED
// only work with LED0,1,2,3
void LED_OFF(uint8_t LEDX);

// toggle one LED
// only work with LED0,1,2,3
void LED_TOGGLE(uint8_t LEDX);

#endif