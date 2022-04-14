#pragma once
#include "raylib.h"
#include "player.h"



struct melee_weapon {
                        Model model;
                        ModelAnimation *anim;
                        unsigned int anim1_fc;
                        Vector3 pos;
                        float theta;
                        Vector3 hit_BB_size;
                        Vector3 hit_BB_pos;
                        BoundingBox hit_BB;
        
};

extern melee_weapon stick;
void create_stick();

void update_player_gear();

