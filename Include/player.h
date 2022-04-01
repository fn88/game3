#include "set_up.h"

extern Model player_model;
extern Vector3 player_size;
extern Vector3 player_pos;
extern Vector3 player_prev_pos;
extern float player_theta;
extern float player_prev_theta;
extern float player_phi;
extern float player_prev_phi;
extern float player_speed;

extern bool player_grounded;
extern bool player_jumped;
extern int player_time_not_grounded;

extern bool player_attack1;

void create_player();
void update_mouse();
void update_player_dir();
void update_player_controls();
void update_player_gravity();
void update_player();




