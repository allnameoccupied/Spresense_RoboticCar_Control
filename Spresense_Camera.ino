//Written by MAX (Created 7-4-2022)

//implementations of functions for Spresense camera contorl
#include "Spresense_Camera.h"
#include <Camera.h>

CameraPictureManager* CameraPictureManager::camera_output_manager = nullptr;

CameraPictureManager::CameraPictureManager(){
    this->camera_output = nullptr;
    this->is_new_image = false;
}

CameraPictureManager* CameraPictureManager::getInstance(){
    if (CameraPictureManager::camera_output_manager == nullptr){
        CameraPictureManager::camera_output_manager = new CameraPictureManager();
    }
    return CameraPictureManager::camera_output_manager;
}

void CameraPictureManager::push_picture(CamImage* new_image){
    camera_output = new_image;
    is_new_image = true;
}

CamImage* CameraPictureManager::pop_picture(){
    if (!is_new_image){return nullptr;}
    is_new_image = false;
    return camera_output;
}

bool CameraPictureManager::is_new_picture_available(){
    return is_new_image;
}

void Camera_start_capturing(){
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
            CameraPictureManager::getInstance()->push_picture(smaller_image);
        }
    }
}

CamImage* Camera_get_image_for_NN(){
    if (!is_camera_capturing){return nullptr;}
    if (!CameraPictureManager::getInstance()->is_new_picture_available()){return nullptr;}
    return CameraPictureManager::getInstance()->pop_picture();
}

void Camera_stop_capturing(){
    camera_util->startStreaming(false,Camera_new_image_handler);
    is_camera_capturing = false;
}