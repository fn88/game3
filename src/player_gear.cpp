#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "player_gear.h"
#include "set_up.h"
#include "audio.h"
#include "collisions.h"

melee_weapon stick {};
unsigned int stick_anims_count = 0;


void create_stick()
{
    stick.model = LoadModel("resources/models/stick.iqm");
    stick.pos = {player.pos.x, player.pos.y, player.pos.z + 1.0f};
    stick.theta = player.theta;
    stick.hit_BB_size = {1.0f, 1.0f, 1.0f};  //{0.2f, 0.2f, 0.2f};
    stick.hit_BB_pos = player.pos;
    stick.hit_BB = { Vector3({stick.hit_BB_pos.x - stick.hit_BB_size.x/2, stick.hit_BB_pos.y - stick.hit_BB_size.y/2, stick.hit_BB_pos.z - stick.hit_BB_size.z/2}), 
                     Vector3({stick.hit_BB_pos.x + stick.hit_BB_size.x/2, stick.hit_BB_pos.y + stick.hit_BB_size.y/2, stick.hit_BB_pos.z + stick.hit_BB_size.z/2}) };

    Texture2D stick_texture = LoadTexture("resources/textures/floor_texture.png");
    stick.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stick_texture;
    stick.anim = LoadModelAnimations("resources/models/stick.iqm", &stick_anims_count);
    stick.anim1_fc = 0;
}


void update_player_gear()
{
    stick.pos = { player.pos.x + (cos(player.phi) * cos(player.theta - PI/8)), 
                  player.pos.y + (cos(player.phi) * sin(player.theta - PI/8)),
                  player.pos.z + sin(player.phi) };
    
    stick.model.transform = MatrixRotateXYZ(Vector3({0.0f, player.phi, -player.theta}));

    if (player.attack1) 
    {
        UpdateModelAnimation(stick.model, stick.anim[0], stick.anim1_fc);

        stick.anim1_fc += 2;
        if (stick.anim1_fc > 60)
        {
            stick.anim1_fc = 0;
            player.attack1 = false;
        }
        if (stick.anim1_fc >= 10 && stick.anim1_fc <= 12) PlaySound(sounds[GetRandomValue(0, 3)]);
        if (stick.anim1_fc >= 30 && stick.anim1_fc <= 32)
        {
            stick.hit_BB_pos = { player.pos.x + (3 * (cos(player.phi) * cos(player.theta))), 
                                 player.pos.y + (3 * (cos(player.phi) * sin(player.theta))),
                                 player.pos.z + (3 * sin(player.phi)) };
            stick.hit_BB = update_BB_pos(stick.hit_BB_size, stick.hit_BB_pos);
                            
            for (auto it = tree_models.begin(); it < tree_models.end(); it++)
            {
                if (CheckCollisionBoxes((*it).BB, stick.hit_BB)) PlaySound(sounds[(GetRandomValue(4, 5))]);
            }
        }
    }
}