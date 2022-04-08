#pragma once
#include "raylib.h"
#include <vector>



struct model_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
};                    

extern model_Obj load_model(const char *model_loc, const char *texture_loc, Vector3 pos);
extern BoundingBox update_BB_pos(BoundingBox box, Vector3 pos, Vector3 size);

extern std::vector<model_Obj> level_models;
extern std::vector<model_Obj> tree_models;


void load_level_models();
void load_tree_models();

