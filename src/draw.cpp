#include "set_up.h"


void draw_level()
{
    DrawModel(level_models[0].model, level_models[0].pos, 1.0f, WHITE);
    DrawModel(level_models[1].model, level_models[1].pos, 1.0f, WHITE);
}

void draw_player()
{
    DrawModel(player_model, player_pos, 1.0f, WHITE);
}

void draw_enemies()
{
    DrawModel(enemy_model, enemy_pos, 1.0f, WHITE);
}

void draw_player_gear()
{
    DrawModel(stick.model, stick.pos, 1.0f, BROWN);
}


void draw_everything()
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(cam);

    draw_level();
    draw_player();
    draw_enemies();
    draw_player_gear();


    EndMode3D();

    DrawFPS(10, 10);
    DrawText(TextFormat("player_theta: %02.02f", player_theta), 50, 40, 30, WHITE);
    DrawText(TextFormat("player_phi: %02.02f", player_phi), 50, 70, 30, WHITE);
    DrawText(TextFormat("player_grounded: %02i", int(player_grounded)), 50, 100, 30, WHITE);
    DrawText(TextFormat("player_time_not_grounded: %02i", player_time_not_grounded), 50, 130, 30, WHITE);
    DrawText(TextFormat("enemy_theta: %02.02f", enemy_theta), 50, 160, 30, WHITE);
    DrawText(TextFormat("enemy_move_poi: %02f, %02f, %02f", enemy_move_poi.x, enemy_move_poi.y, enemy_move_poi.z), 50, 190, 30, WHITE);
    DrawText(TextFormat("player_attack1: %02i", int(player_attack1)), 50, 220, 30, WHITE);
    EndDrawing();
}


