#pragma once
#include "set_up.h"


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

