#include "set_up.h"


Model enemy_model;
Vector3 enemy_size;
Vector3 enemy_pos;
Vector3 enemy_prev_pos;
float enemy_theta;
float enemy_prev_theta;
float enemy_phi;
float enemy_prev_phi;
float enemy_speed;
Vector3 enemy_move_poi;

bool enemy_grounded;
bool enemy_jumped;
int enemy_time_not_grounded;



void create_enemy()
{
    enemy_model = LoadModel("resources/models/player.obj");
    enemy_size = {2.0f, 2.0f, 2.0f};
    enemy_pos = {14.0f, 14.0f, 4.0f};
    enemy_prev_pos = enemy_pos;
    enemy_theta = 0.0f;
    enemy_prev_theta = 0.0f;
    enemy_phi = 0.0f;
    enemy_prev_phi = 0.0f;
    enemy_speed = 0.2f;
    enemy_move_poi = { enemy_pos.x + float(GetRandomValue(-10, 10)), enemy_pos.y + float(GetRandomValue(-10, 10)), enemy_pos.z };

    Texture2D enemy_model_texture = LoadTexture("resources/textures/floor_texture.png");
    enemy_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = enemy_model_texture;
}

void enemy_change_dir(int ticks)
{   
    if (counter1%ticks == 0) 
    //if (abs(enemy_move_poi.x - enemy_pos.x) < 0.1f && abs(enemy_move_poi.y - enemy_pos.y) < 0.1f && abs(enemy_move_poi.z - enemy_pos.z) < 0.1f)
    {
        enemy_move_poi = Vector3{ enemy_pos.x + float(GetRandomValue(-10, 10)), enemy_pos.y + float(GetRandomValue(-10, 10)), enemy_pos.z };
        enemy_theta = atan2((enemy_move_poi.x -  enemy_pos.x), (enemy_move_poi.y - enemy_pos.y));
    }
}

void enemy_move()
{
    enemy_pos.x += enemy_speed * sin(enemy_theta);
    enemy_pos.y += enemy_speed * cos(enemy_theta);
}
void update_enemy()
{
    enemy_prev_pos = enemy_pos;

    enemy_change_dir(120);
    enemy_move();

}