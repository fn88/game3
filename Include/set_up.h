#pragma once 
#include "raylib.h"   


extern int S_W;
extern int S_H;
extern int FPS;
extern int LVL_SIZE_X; 
extern int LVL_SIZE_Y;
extern int LVL_SIZE_Z;
extern Camera cam;
extern float mouse_sensitivity;
extern bool tab_info_hidden;

extern int counter1;
extern int counter2;

void set_up_window();
void set_up_cam();

void update_counters();



