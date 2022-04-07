//Written by MAX (Created 7-4-2022)

//functions for serial communication
#ifndef SERIAL_H
#define SERIAL_H

//send String and wait for answer
String* SERIAL_println_wait_response(const String* const message);

//send String, just send
void Serial_println(const String* const message);

#endif