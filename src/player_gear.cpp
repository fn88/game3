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
    stick.pos = player_pos;
    stick.size = {0.2f, 0.2f, 3.0f};
    stick.theta = player_theta;

    Texture2D stick_texture = LoadTexture("resources/textures/floor_texture.png");
    stick.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stick_texture;

    stick.anim = LoadModelAnimations("resources/models/stick.iqm", &stick_anims_count);
    stick.anim1_fc = 0;
}


void update_player_gear()
{
    stick.pos = { player_pos.x + (cos(player_phi) * cos(player_theta -PI/8)), 
                  player_pos.y + (cos(player_phi) * sin(player_theta - PI/8)),
                  player_pos.z + sin(player_phi) };
    
    stick.model.transform = MatrixRotateXYZ(Vector3({0.0f, player_phi, -player_theta}));

    if (player_attack1) 
    {
        UpdateModelAnimation(stick.model, stick.anim[0], stick.anim1_fc);
        stick.anim1_fc++;
        if (stick.anim1_fc > 59)
        {
            stick.anim1_fc = 0;
            player_attack1 = false;
        }
    }
}