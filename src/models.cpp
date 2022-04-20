#include "raylib.h"
#include "raymath.h"
#include "models.h"
#include "set_up.h"
#include "player.h"

  
std::vector<model_Obj>level_models{};
std::vector<seed_Obj>placed_level_models{};
std::vector<model_Obj> * ptr_level_models = &level_models;
std::vector<seed_Obj> * ptr_placed_level_models = &placed_level_models;

model_Obj pine_tree_models[6] = {};  
std::vector<seed_Obj>seeded_pine_trees{};
std::vector<seed_Obj> * ptr_seeded_pine_trees = &seeded_pine_trees;

model_Obj weeds_models[18] = {};
model_Obj * ptr_weeds_models = &weeds_models[18];
std::vector<seed_Obj> seeded_weeds{};
std::vector<seed_Obj> * ptr_seeded_weeds_models = &seeded_weeds;

void load_level_models()
{

    load_model("resources/models/level_floor.obj", "resources/textures/floor_texture.png", {0.0f, 0.0f, -1.0f});
    load_model("resources/models/ZUParrows.obj", "resources/textures/floor_texture.png", {5.0f, 5.0f, 1.0f});
}

void load_pine_tree_models()
{
    for (int i = 0; i < 6; i++)
    {
        unsigned int rand_frame = GetRandomValue(0, 120);
        pine_tree_models[i] = {LoadModel("resources/models/tree1.iqm"), rand_frame};
        float x = float(GetRandomValue(-30, 30))/600.0f;
        float y = float(GetRandomValue(-30, 30))/600.0f;
        float z = 2*PI/6 * i;
        pine_tree_models[i].model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
        Texture2D tree1_texture = LoadTexture("resources/textures/tree_texture.png");
        pine_tree_models[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tree1_texture;
    }
}

void seed_pine_trees(int n)
{
    for (int i = 0; i < n; i++)
    {
        int variant = GetRandomValue(0, 5);
        BoundingBox tree_BB = {Vector3({-4.0, -4.0, -25.0}), Vector3({4.0, 4.0, 25.0})};
        Vector3 tree_size = {abs(tree_BB.max.x/2), abs(tree_BB.max.y/2), abs(tree_BB.max.z/2)};
        Vector3 tree_pos = {float(GetRandomValue(-100, 100)), float(GetRandomValue(-100, 100)), 0.0f};
        seeded_pine_trees.push_back(seed_Obj{tree_size, tree_pos, update_BB_pos(tree_size, tree_pos), variant});
    }
}

void load_weeds_models()
{
    for (int i = 0; i < 6; i++)
    {
        weeds_models[i] = {LoadModel("resources/models/tobakki1.obj"), 1};
        float x = float(GetRandomValue(-30, 30))/600.0f;
        float y = float(GetRandomValue(-30, 30))/600.0f;
        float z = 2*PI/6 * i;
        weeds_models[i].model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
        Texture2D weed_texture = LoadTexture("resources/textures/floor_texture.png");
        weeds_models[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = weed_texture;
    }
    for (int i = 7; i < 12; i++)
    {
        weeds_models[i] = {LoadModel("resources/models/tobakki2.obj"), 1};
        float x = float(GetRandomValue(-30, 30))/600.0f;
        float y = float(GetRandomValue(-30, 30))/600.0f;
        float z = 2*PI/6 * i;
        weeds_models[i].model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
        Texture2D weed_texture = LoadTexture("resources/textures/floor_texture.png");
        weeds_models[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = weed_texture;
    }
    for (int i = 13; i < 18; i++)
    {
        weeds_models[i] = {LoadModel("resources/models/tobakki3.obj"), 1};
        float x = float(GetRandomValue(-30, 30))/600.0f;
        float y = float(GetRandomValue(-30, 30))/600.0f;
        float z = 2*PI/6 * i;
        weeds_models[i].model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
        Texture2D weed_texture = LoadTexture("resources/textures/floor_texture.png");
        weeds_models[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = weed_texture;
    }
}

void seed_weeds(int n)
{
    for (int i = 0; i < n; i++)
    {
        int variant = GetRandomValue(0, 17);
        BoundingBox weed_BB = GetModelBoundingBox(weeds_models[variant].model); 
        Vector3 weed_size = {abs(weed_BB.max.x/2), abs(weed_BB.max.y/2), abs(weed_BB.max.z/2)};
        Vector3 weed_pos = {float(GetRandomValue(-100, 100)), float(GetRandomValue(-100, 100)), 0.0f};
        seeded_weeds.push_back(seed_Obj{weed_size, weed_pos, update_BB_pos(weed_size, weed_pos), variant});
    }
}







/*void load_tobakki_models()
{
    for (int i = 0; i < 100; i++)
    {
        float x = float(GetRandomValue(-100, 100));
        float y = float(GetRandomValue(-100, 100));
        float z = 1.0f;
        tobakki_models.push_back(load_tobakki_model("resources/models/tobakki1.obj", "resources/textures/floor_texture.png", {x, y, z}));
        x = float(GetRandomValue(-100, 100));
        y = float(GetRandomValue(-100, 100));
        z = 1.0f;
        tobakki_models.push_back(load_tobakki_model("resources/models/tobakki2.obj", "resources/textures/floor_texture.png", {x, y, z}));
        x = float(GetRandomValue(-100, 100));
        y = float(GetRandomValue(-100, 100));
        z = 1.0f;
        tobakki_models.push_back(load_tobakki_model("resources/models/tobakki3.obj", "resources/textures/floor_texture.png", {x, y, z}));
    }
    for (auto it = tobakki_models.begin(); it < tobakki_models.end(); it++)
    {
        (*it).BB = update_BB_pos((*it).size, {(*it).pos.x, (*it).pos.y, (*it).pos.z + (*it).size.z/2});
        float x = float(GetRandomValue(-30, 30))/400.0f;
        float y = float(GetRandomValue(-30, 30))/400.0f;
        float z = float(GetRandomValue(-3, 3));
        (*it).model.transform = MatrixRotateXYZ(Vector3({x, y, z}));
    }
}
std::vector<model_Obj> * ptr_tobakki_models = &tobakki_models; */


BoundingBox update_BB_pos(Vector3 size, Vector3 pos)
{
    BoundingBox moved_box = {Vector3({  pos.x - size.x/2, 
                                        pos.y - size.y/2, 
                                        pos.z - size.z/2}), 
                             Vector3({  pos.x + size.x/2, 
                                        pos.y + size.y/2, 
                                        pos.z + size.z/2}) };
    return moved_box;
} 

void load_model(const char *model_loc, const char *texture_loc, Vector3 model_pos)
{
    Model model = LoadModel(model_loc);
    Texture2D texture = LoadTexture(texture_loc);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    BoundingBox BB = GetModelBoundingBox(model);
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};
    level_models.push_back(model_Obj{model, 1});
    placed_level_models.push_back(seed_Obj{size, model_pos, update_BB_pos(size, model_pos), 1});
}

/*model_Obj load_tobakki_model(const char *model_loc, const char *texture_loc, Vector3 model_pos)   //temp
{
    Model model = LoadModel(model_loc);
    Texture2D texture = LoadTexture(texture_loc);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    //BoundingBox BB = GetModelBoundingBox(model);
    BoundingBox BB = {Vector3({-1.0f, -1.0f, 0.0f}), Vector3({1.0f, 1.0f, 0.2f})};
    Vector3 size = {BB.max.x - BB.min.x, BB.max.y - BB.min.y, BB.max.z - BB.min.z};
    unsigned int rv1 = GetRandomValue(1, 120);
    return model_Obj{model, size, model_pos, update_BB_pos(size, model_pos), rv1};
}*/


unsigned int pine_tree_anims_count = 0;
ModelAnimation *pine_tree_anims = LoadModelAnimations("resources/models/tree1.iqm", &pine_tree_anims_count);

void update_pine_tree_anims()
{
    for (int i = 0; i < 6; i++)
    {
        pine_tree_models[i].anim_fc++;
        if (pine_tree_models[i].anim_fc > 120) pine_tree_models[i].anim_fc = 1;
        UpdateModelAnimation(pine_tree_models[i].model, pine_tree_anims[0], pine_tree_models[i].anim_fc);
    }
}


