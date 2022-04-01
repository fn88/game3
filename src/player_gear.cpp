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
    //stick.model.transform = MatrixRotateY(PI/2);

    stick.anim = LoadModelAnimations("resources/models/stick.iqm", &stick_anims_count);
    stick.anim1_fc = 0;
}


void update_player_gear()
{
    stick.pos = { player_pos.x + (cos(player_phi) * cos(player_theta)), 
                  player_pos.y + (cos(player_phi) * sin(player_theta)),
                  player_pos.z + sin(player_phi) };
    
    //stick.model.transform = MatrixRotateY(-player_theta);
    stick.model.transform = MatrixRotateZ(-player_theta);

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