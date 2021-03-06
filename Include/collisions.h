#pragma once
#include "raylib.h"
#include "player.h"
#include "models.h"
#include <vector>



void get_bounding_box(std::vector<model_Obj> models_vector);

void gravity_collisions(std::vector<seed_Obj> * models, entity_Obj * entity);
void collisions(std::vector<seed_Obj> * models, entity_Obj * entity);
void player_collisions();
void bullets_collisions();

void all_collisions();


