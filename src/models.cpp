#include "raylib.h"
#include "raymath.h"
#include "models.h"
#include "set_up.h"


std::vector<model_Obj>level_models{};
std::vector<model_Obj>tree_models{};

void load_level_models()
{
    level_models.push_back(load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png", {0.0f, 0.0f, 0.0f} ));
    level_models.push_back(load_model("resources/models/ZUParrows.obj", "resources/textures/floor_texture.png", {5.0f, 5.0f, 2.0f}));
    level_models.push_back(load_model("resources/models/ZUParrows.obj", "resources/textures/floor_texture.png", {25.0f, 25.0f, 2.0f}));
}

void load_tree_models()
{
    tree_models.push_back(load_model("resources/models/tree1_trunk.obj", "resources/textures/floor_texture.png", {-10.0f, -10.0f, 0.0f}));
}

BoundingBox update_BB_pos(BoundingBox box, Vector3 pos, Vector3 size)
{
    BoundingBox moved_box = {Vector3({  pos.x - size.x/2, 
                                        pos.y - size.y/2, 
                                        pos.z - size.z/2}), 
                             Vector3({  pos.x + size.x/2, 
                                        pos.y + size.y/2, 
                                        pos.z + size.z/2}) };
    return moved_box;
} 


model_Obj load_model(const char *model_loc, const char *texture_loc, Vector3 model_pos)
{
    Model model = LoadModel(model_loc);
    Texture2D texture = LoadTexture(texture_loc);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    BoundingBox BB = GetModelBoundingBox(model);
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};

    return model_Obj{model, size, model_pos, update_BB_pos(BB, model_pos, size)};
}

