#include "raylib.h"
#include "raymath.h"
#include "models.h"
#include "collisions.h"
#include "enemies.h"
#include "player_gear.h"
#include "input.h"
#include "set_up.h"


Model player_model;
Vector3 player_pos{}; 
Vector3 player_size{};
Vector3 player_prev_pos{};
BoundingBox player_BB;
BoundingBox player_prev_BB;
float player_theta;
float player_prev_theta;
float player_phi;
float player_prev_phi;
float player_speed ;

bool player_grounded = true;
bool player_colliding = false; //temp

bool player_jumped = false;
int player_time_not_grounded = 0;

bool player_attack1 = false;


void create_player()
{
    player_model = LoadModel("resources/models/player.obj");
    player_size = {2.0f, 2.0f, 2.0f};
    player_pos = {0.0f, 0.0f, 2.5f};
    player_prev_pos = player_pos;
    player_BB = GetModelBoundingBox(player_model);
    player_prev_BB = player_BB;
    player_theta = 0.0f;
    player_prev_theta = 0.0f;
    player_phi = 0.0f;
    player_prev_phi = 0.0f;
    player_speed = 0.2f;

    Texture2D player_model_texture = LoadTexture("resources/textures/floor_texture.png");
    player_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_model_texture;
}

void update_player_dir()
{
    player_prev_theta = player_theta;                
    player_prev_phi = player_phi;                   
    player_theta -= theta;                        
    player_phi -= phi;                                
    if (player_phi >  PI/2.2f) player_phi =  PI/2.2f;
    if (player_phi < -PI/2.2f) player_phi = -PI/2.2f;

    cam.position = player_pos;
    cam.target.y = player_pos.y + (cos(player_phi) * sin(player_theta));
    cam.target.z = player_pos.z + sin(player_phi);
    cam.target.x = player_pos.x + (cos(player_phi) * cos(player_theta));
}

void update_player_BB()
{
    player_BB = update_BB_pos(player_BB, player_pos, player_size);
}

void update_player_gravity() 
{
    if (!player_grounded)
    {
        player_time_not_grounded += 1;
        player_pos.z += (-1.0f) * pow(float(player_time_not_grounded)/FPS, 2); // -9.8/2 ~ -5   (1/2 * gravity * t^2 kinematics eq.)
    }
    if (player_grounded) 
    {
        player_time_not_grounded = 0;
        player_jumped = false;
    }
    if (player_jumped) 
    {
        player_pos.z += 0.3f;
        player_grounded = false;
    }

    update_player_BB();
}


void update_player()
{

    update_player_gravity();

    player_collisions();
    //update_player_BB();
    update_player_dir();

    player_prev_pos = player_pos;
    player_prev_BB = player_BB;
}








