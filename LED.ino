//Written by MAX (Created 7-4-2022)

//implementations of functions for LED control on Spresense
#include "LED.h"

void LED_ONOFF_Control(uint8_t LEDX, bool ONorOFF){
    if(LEDX == LED0){
        digitalWrite(LED0, ONorOFF);
        is_LED_0_ON = ONorOFF;
    }
    if(LEDX == LED1){
        digitalWrite(LED1, ONorOFF);
        is_LED_1_ON = ONorOFF;
    }
    if(LEDX == LED2){
        digitalWrite(LED2, ONorOFF);
        is_LED_2_ON = ONorOFF;
    }
    if(LEDX == LED3){
        digitalWrite(LED3, ONorOFF);
        is_LED_3_ON = ONorOFF;
    }
}

void LED_ON(uint8_t LEDX){
    LED_ONOFF_Control(LEDX,HIGH);
}

void LED_OFF(uint8_t LEDX){
    LED_ONOFF_Control(LEDX,LOW);
}

void LED_TOGGLE(uint8_t LEDX){
    if(LEDX == LED0){
        LED_ONOFF_Control(LED0,!is_LED_0_ON);
    }
    if(LEDX == LED1){
        LED_ONOFF_Control(LED1,!is_LED_1_ON);
    }
    if(LEDX == LED2){
        LED_ONOFF_Control(LED2,!is_LED_2_ON);
    }
    if(LEDX == LED3){
        LED_ONOFF_Control(LED3,!is_LED_3_ON);
    }
}