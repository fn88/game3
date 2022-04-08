#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "player_gear.h"
#include "models.h"
#include "enemies.h"
#include "set_up.h"


void draw_level()
{
    for (auto it = level_models.begin(); it < level_models.end(); it++)
    {
        DrawModel((*it).model, (*it).pos, 1.0f, WHITE);
        DrawBoundingBox((*it).BB, GREEN);
    }
    for (auto it = tree_models.begin(); it < tree_models.end(); it++)
    {
        DrawModel((*it).model, (*it).pos, 1.0f, BROWN);
        DrawBoundingBox((*it).BB, GREEN);
    }
}

void draw_player()
{
    DrawModel(player_model, player_pos, 1.0f, WHITE);
    DrawBoundingBox(player_BB, GREEN);
}

void draw_player_gear()
{
    DrawModel(stick.model, stick.pos, 1.0f, BROWN);
}

void draw_enemies()
{
    DrawModel(enemy_model, enemy_pos, 1.0f, WHITE);
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
    DrawText(TextFormat("player_colliding: %02i", int(player_colliding)), 50, 250, 30, WHITE);
    DrawText(TextFormat("player_pos: %01f, %01f, %01f", player_pos.x, player_pos.y, player_pos.z), 50, 280, 30, WHITE);
    DrawText(TextFormat("player_size: %02f, %02f, %02f", player_size.x, player_size.y, player_size.z), 50, 310, 30, WHITE);
    EndDrawing();
}


