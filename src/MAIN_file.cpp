#include "raylib.h"
#include "player.h"
#include "player_gear.h"
#include "input.h"
#include "game_update.h"
#include "enemies.h"
#include "projectiles.h"
#include "models.h"
#include "draw.h"
#include "set_up.h"
#include "audio.h"


int main()
{
    set_up_window();
    set_up_cam();
    create_player();
    create_stick();
    create_enemy();

    load_level_models();
    load_tree_models();
    load_tobakki_models();

    load_sounds();
    play_bg_music();

    while (!WindowShouldClose())
    {
        update_audio();
        update_input();
        update_player();
        update_player_gear();
        update_enemy();
        update_projectiles();
        update_tree_anims();
        //all_collisions();
        draw_everything();
        

        update_counters();
        
    }

    CloseWindow();
    return 0;
}
