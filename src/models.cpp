#include "raylib.h"
#include "raymath.h"
#include "models.h"
#include "set_up.h"
#include "player.h"


std::vector<model_Obj>level_models{};
std::vector<model_Obj>tree_models{};
Vector3 tree_spots[] = {0};

void load_level_models()
{
    level_models.push_back(load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png", {0.0f, 0.0f, 0.0f}));
    level_models.push_back(load_model("resources/models/ZUParrows.obj", "resources/textures/floor_texture.png", {5.0f, 5.0f, 2.0f}));
    level_models.push_back(load_model("resources/models/ZUParrows.obj", "resources/textures/floor_texture.png", {25.0f, 25.0f, 2.0f}));
}
std::vector<model_Obj> * ptr_level_models = &level_models;

void gen_tree_spots(int n)
{
    for (int i = 0; i < n; i++)
    {
        float x = float(GetRandomValue(-200, 200));
        float y = float(GetRandomValue(-200, 200));
        float z = 0.0f;
        tree_spots[i] = Vector3({x, y, z});
    }
}

void load_tree_models()
{
    for (int i = 0; i < 100; i++)
    {
        float x = float(GetRandomValue(-100, 100));
        float y = float(GetRandomValue(-100, 100));
        float z = 0.0f;
        tree_models.push_back(load_tree_model("resources/models/tree1.iqm", "resources/textures/floor_texture.png", {x, y, z}));
    }
    for (auto it = tree_models.begin(); it < tree_models.end(); it++)
    {
        (*it).BB = update_BB_pos((*it).BB, (*it).size, {(*it).pos.x, (*it).pos.y, (*it).pos.z + (*it).size.z/2});
        float x = float(GetRandomValue(-30, 30))/400.0f;
        float y = float(GetRandomValue(-30, 30))/400.0f;
        float z = float(GetRandomValue(-30, 30))/400.0f;
        (*it).model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
    }
}

/*void load_tree_models()
{
    gen_tree_spots(10);
    tree_models.push_back(load_model("resources/models/tree1_trunk.obj", "resources/textures/floor_texture.png", {-10.0f, -10.0f, 0.0f}));
    for (auto it = tree_models.begin(); it < tree_models.end(); it++)
    {
        (*it).BB = update_BB_pos((*it).BB, (*it).size, {(*it).pos.x, (*it).pos.y, (*it).pos.z + (*it).size.z/2});
    }
}*/
std::vector<model_Obj> * ptr_tree_models = &tree_models;


BoundingBox update_BB_pos(BoundingBox box, Vector3 size, Vector3 pos)
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
    //BoundingBox BB = {Vector3({-1.0f, -1.0f, 0.0f}), Vector3({1.0f, 1.0f, 10.0f})};
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};

    return model_Obj{model, size, model_pos, update_BB_pos(BB, size, model_pos)};
}

model_Obj load_tree_model(const char *model_loc, const char *texture_loc, Vector3 model_pos)   //temp
{
    Model model = LoadModel(model_loc);
    Texture2D texture = LoadTexture(texture_loc);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    //BoundingBox BB = GetModelBoundingBox(model);
    BoundingBox BB = {Vector3({-1.0f, -1.0f, 0.0f}), Vector3({1.0f, 1.0f, 10.0f})};
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};
    unsigned int rv1 = GetRandomValue(1, 120);
    return model_Obj{model, size, model_pos, update_BB_pos(BB, size, model_pos), rv1};
}


unsigned int tree_anims_count = 0;
ModelAnimation *tree_anim = LoadModelAnimations("resources/models/tree1.iqm", &tree_anims_count);
void update_tree_anims()
{
    for (auto it = tree_models.begin(); it < tree_models.end(); it++)
    {
        UpdateModelAnimation((*it).model, tree_anim[0], (*it).anim_fc);
        (*it).anim_fc++;
        if ((*it).anim_fc > 120) (*it).anim_fc = 1;
    }
}


