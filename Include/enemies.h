#pragma once
#include "raylib.h"
#include "player.h"
#include "models.h"


extern Model enemy_model;
extern Vector3 enemy_size;
extern Vector3 enemy_pos;
extern Vector3 enemy_prev_pos;
extern float enemy_theta;
extern float enemy_prev_theta;
extern float enemy_phi;
extern float enemy_prev_phi;
extern float enemy_speed;
extern Vector3 enemy_move_poi;

extern bool enemy_grounded;
extern bool enemy_jumped;
extern int enemy_time_not_grounded;



void enemy_change_dir(int ticks);
void enemy_move();
void update_enemy_gravity();
void update_enemy();


void create_enemy();



