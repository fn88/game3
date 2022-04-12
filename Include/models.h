#pragma once
#include "raylib.h"
#include <vector>



struct model_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
                    unsigned int anim_fc;
};                    

extern model_Obj load_model(const char *model_loc, const char *texture_loc, Vector3 pos);
extern model_Obj load_tree_model(const char *model_loc, const char *texture_loc, Vector3 pos);  //temp
extern BoundingBox update_BB_pos(BoundingBox box, Vector3 pos, Vector3 size);

extern std::vector<model_Obj> level_models;
extern std::vector<model_Obj> * ptr_level_models;
extern std::vector<model_Obj> tree_models;
extern std::vector<model_Obj> * ptr_tree_models;
extern Vector3 tree_spots[];



void load_level_models();
void load_tree_models();
void get_tree_spots(int n);
void update_tree_anims();

