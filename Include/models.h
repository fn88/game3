#pragma once
#include "raylib.h"
#include <vector>


struct model_Obj {
                    Model model;
                    unsigned int anim_fc;
};


struct seed_Obj {
                    Vector3 size;
                    Vector3 pos;
                    BoundingBox BB;
                    int model_variant;
};          

extern void load_model(const char *model_loc, const char *texture_loc, Vector3 pos);

extern BoundingBox update_BB_pos(Vector3 size, Vector3 pos);

extern std::vector<model_Obj> level_models;
extern std::vector<seed_Obj> placed_level_models;
extern std::vector<model_Obj> * ptr_level_models;
extern std::vector<seed_Obj> * ptr_placed_level_models;
void load_level_models();

extern model_Obj pine_tree_models[];   
extern std::vector<seed_Obj> seeded_pine_trees;
extern model_Obj * ptr_pine_tree_models;
extern std::vector<seed_Obj> * ptr_seeded_pine_trees;
void load_pine_tree_models();
void seed_pine_trees(int n);
void update_pine_tree_anims();

extern model_Obj weeds_models[];
extern std::vector<seed_Obj> seeded_weeds;
extern model_Obj * ptr_weeds_models;
extern std::vector<seed_Obj> * ptr_seeded_weeds;
void load_weeds_models();
void seed_weeds(int n);



