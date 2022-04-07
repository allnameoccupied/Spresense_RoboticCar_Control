//Written by MAX (Created 7-4-2022)

//functions for Spresense camera contorl
#ifndef SPRESENSE_CAMERA_H
#define SPRESENSE_CAMERA_H

#include <Camera.h>

// all functions are just for getting images to feed to neural network

#define NN_INPUT_IMAGE_SIZE 28

// assistant class for managing camera output
class CameraPictureManager{
    private:
    static CameraPictureManager* camera_output_manager;
    CamImage* camera_output;
    bool is_new_image;

    public:
    CameraPictureManager();
    static CameraPictureManager* getInstance();
    void push_picture(CamImage* new_image);
    CamImage* pop_picture();
    bool is_new_picture_available();

};

static bool is_camera_capturing;
static CameraClass* camera_util;

// start constantly capturing images using startStreaming()
void Camera_start_capturing();

// call this function to get image(28x28) for neural network
// always return null pointer if camera not yet started capturing
// output CamImage format: 28x28, YUV422
CamImage* Camera_get_image_for_NN();

// stop capturing images
void Camera_stop_capturing();

#endif