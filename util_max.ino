// implementation of the utility functions
#include "util_max.h"

// 1 = LED
void LED_OnOff_control_M(uint8_t LEDX, bool is_turnOn){
    switch (LEDX){
        case LED0:
            digitalWrite(LED0, is_turnOn);
            is_LED_0_ON = is_turnOn;
            break;

        case LED1:
            digitalWrite(LED1, is_turnOn);
            is_LED_1_ON = is_turnOn;
            break;
        
        case LED2:
            digitalWrite(LED2, is_turnOn);
            is_LED_2_ON = is_turnOn;
            break;

        case LED3:
            digitalWrite(LED3, is_turnOn);
            is_LED_3_ON = is_turnOn;
            break;
        
        default:
            break;
    }
}

void LED_turnON_M(uint8_t LEDX){
    LED_OnOff_control_M(LEDX,HIGH);
}

void LED_turnOFF_M(uint8_t LEDX){
    LED_OnOff_control_M(LEDX,LOW);
}

void LED_toggle_M(uint8_t LEDX){
    switch (LEDX){
        case LED0:
            LED_OnOff_control_M(LEDX,!is_LED_0_ON);
            break;

        case LED1:
            LED_OnOff_control_M(LEDX,!is_LED_1_ON);
            break;
        
        case LED2:
            LED_OnOff_control_M(LEDX,!is_LED_2_ON);
            break;

        case LED3:
            LED_OnOff_control_M(LEDX,!is_LED_3_ON);
            break;
        
        default:
            break;
    }
}


// 2 = SERIAL
String* SERIAL_println_wait_response_max(const String* const message_for_user){
    Serial.println(*message_for_user);
    while (!Serial.available());
    return &(Serial.readString());
}


// 3 = CAMERA
CameraPictureManagerM* CameraPictureManagerM::camera_output_manager = nullptr;

CameraPictureManagerM::CameraPictureManagerM(){
    this->camera_output = nullptr;
    this->is_new_image = false;
}

CameraPictureManagerM* CameraPictureManagerM::getInstance(){
    if (CameraPictureManagerM::camera_output_manager == nullptr){
        CameraPictureManagerM::camera_output_manager = new CameraPictureManagerM();
    }
    return CameraPictureManagerM::camera_output_manager;
}

void CameraPictureManagerM::push_picture(CamImage* new_image){
    camera_output = new_image;
    is_new_image = true;
}

CamImage* CameraPictureManagerM::pop_picture(){
    if (!is_new_image){return nullptr;}
    is_new_image = false;
    return camera_output;
}

bool CameraPictureManagerM::is_new_picture_available(){
    return is_new_image;
}

void Camera_start_capturing_M(){
    is_camera_capturing = true;
    camera_util->startStreaming(true,Camera_new_image_handler);
}

void Camera_new_image_handler(CamImage new_img){
    if (new_img.isAvailable()){
        new_img.convertPixFormat(CAM_IMAGE_PIX_FMT_YUV422);
        CamImage* smaller_image;
        new_img.clipAndResizeImageByHW(
            *smaller_image,
            48,8,271,231,
            NN_INPUT_IMAGE_SIZE,NN_INPUT_IMAGE_SIZE);
        if (smaller_image->isAvailable()){
            CameraPictureManagerM::getInstance()->push_picture(smaller_image);
        }
    }
}

CamImage* Camera_get_image_for_NN_M(){
    if (!is_camera_capturing){return nullptr;}
    if (!CameraPictureManagerM::getInstance()->is_new_picture_available()){return nullptr;}
    return CameraPictureManagerM::getInstance()->pop_picture();
}

void Camera_stop_capturing_M(){
    camera_util->startStreaming(false,Camera_new_image_handler);
    is_camera_capturing = false;
}