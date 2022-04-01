#include "set_up.h"


std::vector<model_Obj>level_models{};

void load_models()
{
    level_models.push_back(model_Obj{   LoadModel("resources/models/level_floor.obj"), 
                                        {200.0f, 200.0f, 2.0f},    // size
                                        {0.0f, 0.0f, -1.0f} });  // pos
    /*level_models.push_back(model_Obj{   LoadModel("resources/models/ZUParrows.obj"), 
                                        {2.0f, 2.0f, 2.0f},    // size
                                        {0.0f, 0.0f, 2.0f} });  // pos   */                                 
    Texture2D floor_10x10_model_texture = LoadTexture("resources/textures/floor_texture.png");
    level_models[0].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor_10x10_model_texture;

}
