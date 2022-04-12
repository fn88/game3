#include "raylib.h"
#include "raymath.h"
#include "models.h"
#include "collisions.h"
#include "enemies.h"
#include "player_gear.h"
#include "input.h"
#include "set_up.h"


entity_Obj player{0};


void create_player()
{
    player.model = LoadModel("resources/models/player.obj");
    player.size = {2.0f, 2.0f, 2.0f};
    player.pos = {0.0f, 0.0f, 4.5f};
    player.prev_pos = player.pos;
    player.BB = GetModelBoundingBox(player.model);
    player.prev_BB = player.BB;
    player.theta = 0.0f;
    player.prev_theta = 0.0f;
    player.phi = 0.0f;
    player.prev_phi = 0.0f;
    player.speed = 10.0f;
    player.grounded = true;
    player.jumped = false;
    player.time_not_grounded = 0;
    player.attack1 = false;
    player.action1 = false;
    player.colliding = false;

    Texture2D player_model_texture = LoadTexture("resources/textures/floor_texture.png");
    player.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_model_texture;
}

entity_Obj * ptr_player = &player;

void update_player_dir()
{
    player.prev_theta = player.theta;                
    player.prev_phi = player.phi;                   
    player.theta -= theta;                        
    player.phi -= phi;                                
    if (player.phi >  PI/2.2f) player.phi =  PI/2.2f;
    if (player.phi < -PI/2.2f) player.phi = -PI/2.2f;

    cam.position = player.pos;
    cam.target.y = player.pos.y + (cos(player.phi) * sin(player.theta));
    cam.target.z = player.pos.z + sin(player.phi);
    cam.target.x = player.pos.x + (cos(player.phi) * cos(player.theta));
}

void update_player_BB()
{
    player.BB = update_BB_pos(player.BB, player.size, player.pos);
}

void update_player_gravity() 
{
    if (!player.grounded)
    {
        player.time_not_grounded += 1;
        player.pos.z += (-1.0f) * pow(float(player.time_not_grounded)/FPS, 2); // -9.8/2 ~ -5   (1/2 * gravity * t^2 kinematics eq.)
    }
    if (player.grounded) 
    {
        player.time_not_grounded = 0;
        player.jumped = false;
    }
    if (player.jumped) 
    {
        player.pos.z += 0.3f;
        player.grounded = false;
    }

    update_player_BB();
}


void update_player()
{

    update_player_gravity();

    player_collisions();
    update_player_dir();

    player.prev_pos = player.pos;
    player.prev_BB = player.BB;
}








