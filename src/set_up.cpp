#include "set_up.h"


int S_W = 1600;
int S_H = 1000;
int FPS = 60;
float mouse_sensitivity = 3.0f;

int counter1 = 0;  //  for various timing, delays 
int counter2 = 0;
int LVL_SIZE_X = 1000;
int LVL_SIZE_Y = 1000;
int LVL_SIZE_Z = 1000;
Camera cam = {0};

void set_up_window()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(S_W, S_H, "game3");
    SetMousePosition(S_W/2.0f, S_H/2.0f);
    HideCursor();
    SetTargetFPS(FPS);
    //InitAudioDevice();
}

void set_up_cam()
{
    cam.fovy = 40.0f;
    cam.up = {0.0f, 0.0f, 1.0f};
    cam.projection = CAMERA_PERSPECTIVE;
    cam.position = {10.0f, 10.0f, 10.0f};
    cam.target = {0.0f, 0.0f, 0.0f};
}



