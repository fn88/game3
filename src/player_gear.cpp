#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "player_gear.h"
#include "set_up.h"

melee_weapon stick {};
unsigned int stick_anims_count = 0;


void create_stick()
{
    stick.model = LoadModel("resources/models/stick.iqm");
    stick.pos = player.pos;
    stick.size = {0.2f, 0.2f, 3.0f};
    stick.theta = player.theta;

    Texture2D stick_texture = LoadTexture("resources/textures/floor_texture.png");
    stick.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stick_texture;

    stick.anim = LoadModelAnimations("resources/models/stick.iqm", &stick_anims_count);
    stick.anim1_fc = 0;
}


void update_player_gear()
{
    stick.pos = { player.pos.x + (cos(player.phi) * cos(player.theta -PI/8)), 
                  player.pos.y + (cos(player.phi) * sin(player.theta - PI/8)),
                  player.pos.z + sin(player.phi) };
    
    stick.model.transform = MatrixRotateXYZ(Vector3({0.0f, player.phi, -player.theta}));

    if (player.attack1) 
    {
        UpdateModelAnimation(stick.model, stick.anim[0], stick.anim1_fc);
        stick.anim1_fc++;
        if (stick.anim1_fc > 59)
        {
            stick.anim1_fc = 0;
            player.attack1 = false;
        }
    }
}