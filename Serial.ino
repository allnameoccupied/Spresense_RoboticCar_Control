//Written by MAX (Created 7-4-2022)

//implementations of functions for serial communication
#include "Serial.h"

String* SERIAL_println_wait_response(const String* const message){
    Serial.println(*message);
    while (!Serial.available());
    return &(Serial.readString());
}

void Serial_println(const String* const message){
    Serial.println(*message);
}