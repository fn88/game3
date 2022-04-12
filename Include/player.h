#pragma once
#include "raylib.h"
#include "set_up.h"


extern bool player_colliding;
struct entity_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    Vector3 prev_pos;
                    BoundingBox BB;
                    BoundingBox prev_BB;
                    float theta;
                    float prev_theta;
                    float phi;
                    float prev_phi;
                    float speed;
                    bool grounded;
                    bool jumped;
                    int time_not_grounded;
                    bool attack1;
                    bool action1;
                    bool colliding;
};

extern entity_Obj player;
extern entity_Obj * ptr_player;


/*extern Model player_model;
extern Vector3 player_size;
extern Vector3 player_pos;
extern Vector3 player_prev_pos;
extern BoundingBox player_BB;
extern BoundingBox player_prev_BB;
extern float player_theta;
extern float player_prev_theta;
extern float player_phi;
extern float player_prev_phi;
extern float player_speed;

extern bool player_grounded;
extern bool player_colliding;

extern bool player_jumped;
extern int player_time_not_grounded;

extern bool player_attack1; */

void create_player();
void update_mouse();
void update_player_dir();
void update_player_controls();
void update_player_gravity();
void update_player();
void update_player_BB();




