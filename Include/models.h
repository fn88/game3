#pragma once
#include "raylib.h"
#include <vector>


struct model_Obj {
                    Model model;
                    Vector3 size;
                    Vector3 pos;
};                    

extern std::vector<model_Obj> level_models;

void load_models();
