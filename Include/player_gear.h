#pragma once
#include "raylib.h"
#include "player.h"



struct melee_weapon {
                                Model model;
                                ModelAnimation *anim;
                                unsigned int anim1_fc;
                                Vector3 pos;
                                Vector3 size;
                                float theta;
};

extern melee_weapon stick;
void create_stick();

void update_player_gear();

