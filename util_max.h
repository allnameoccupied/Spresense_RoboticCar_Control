// some utility functions
#ifndef UTIL_MAX_H
#define UTIL_MAX_H

#include <Camera.h>

// 1 = LED
// 2 = SERIAL
// 3 = CAMERA


// 1 = LED

// ON/OFF state of each LED
static bool is_LED_0_ON;
static bool is_LED_1_ON;
static bool is_LED_2_ON;
static bool is_LED_3_ON;

// turn on one LED
// only work with LED0,1,2,3
void LED_turnON_M(uint8_t LEDX);

// turn off one LED
// only work with LED0,1,2,3
void LED_turnOFF_M(uint8_t LEDX);

// toggle one LED
// only work with LED0,1,2,3
void LED_toggle_M(uint8_t LEDX);


// 2 = SERIAL

// send String and wait for answer
String* SERIAL_println_wait_response_M(const String* const message_for_user);


// 3 = CAMERA
// all functions are just for getting images to feed to neural network

#define NN_INPUT_IMAGE_SIZE 28

// assistant class for managing camera output
class CameraPictureManagerM{
    private:
    static CameraPictureManagerM* camera_output_manager;
    CamImage* camera_output;
    bool is_new_image;

    public:
    CameraPictureManagerM();
    static CameraPictureManagerM* getInstance();
    void push_picture(CamImage* new_image);
    CamImage* pop_picture();
    bool is_new_picture_available();

};

static bool is_camera_capturing;
static CameraClass* camera_util;

// start constantly capturing images using startStreaming()
void Camera_start_capturing_M();

// call this function to get image(28x28) for neural network
// always return null pointer if camera not yet started capturing
// output CamImage format: 28x28, YUV422
CamImage* Camera_get_image_for_NN_M();

// stop capturing images
void Camera_stop_capturing_M();











#endif