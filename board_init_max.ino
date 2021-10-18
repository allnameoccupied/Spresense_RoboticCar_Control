//implementations of functions for initialization
#include "board_init_max.h"
// #include <pins_arduino.h>

void LED_init_max(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

void PIN_init_max(const uint8_t pin_list[]){
    for (uint8_t i = 0; i < sizeof pin_list / sizeof pin_list[0]; i++)
    {
        PIN_init_max(pin_list[i]);
    }
    
}

void PIN_init_max(const uint8_t pin){
    pinMode(pin, OUTPUT);
}