#pragma once
#include "raylib.h"
#include "models.h"
#include "player.h"
#include "set_up.h"
#include "projectiles.h"


extern bool boxCollideDetect(Vector3 box_A_pos, Vector3 box_A_size, Vector3 box_B_pos, Vector3 box_B_size);

void player_collisions();
void bullets_collisions();

void all_collisions();


