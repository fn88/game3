#include "set_up.h"


int main()
{
    set_up_window();
    set_up_cam();
    create_player();
    create_stick();
    create_enemy();
    load_models();
    

    while (!WindowShouldClose())
    {
        update_input();
        update_player();
        update_player_gear();
        update_enemy();
        update_projectiles();
        all_collisions();
        draw_everything();

        update_counters();
        
    }

    CloseWindow();
    return 0;
}
