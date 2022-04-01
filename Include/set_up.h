#pragma once  // include all headers here and only include the set_up.h header everywhere else
#include <vector>
#include <cmath>
#include "raymath.h"
#include "raylib.h"   
#include "player.h"
#include "collisions.h"
#include "enemies.h"
#include "game_update.h"
#include "draw.h"
#include "projectiles.h"
#include "models.h"
#include "controls.h"
#include "player_gear.h"



extern int S_W;
extern int S_H;
extern int FPS;
extern int LVL_SIZE_X; 
extern int LVL_SIZE_Y;
extern int LVL_SIZE_Z;
extern Camera cam;
extern float mouse_sensitivity;

extern int counter1;
extern int counter2;

void set_up_window();
void set_up_cam();

void update_counters();



