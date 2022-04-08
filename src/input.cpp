#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "set_up.h"

// mouse
float theta;
float phi;
float mousePosX;
float mousePosY;
float mouseDistX;
float mouseDistY;

void update_mouse()
{
    mousePosX = (float)GetMouseX();
    mousePosY = (float)GetMouseY();
    mouseDistX = mouse_sensitivity * (mousePosX - (S_W/2.0f));
    mouseDistY = mouse_sensitivity * (mousePosY - (S_H/2.0f));
    SetMousePosition(S_W/2.0f, S_H/2.0f);
    theta = mouseDistX/(S_W/2.0f) * (cam.fovy/2.0f) * DEG2RAD; 
    phi = mouseDistY/(S_H/2.0f) * (cam.fovy/2.0f) * DEG2RAD;
}


void update_player_controls()
{
    if (IsMouseButtonPressed(0)) player_attack1 = true;

    if (IsKeyDown(KEY_W))
    {
        player_pos.x += player_speed * cos(player_theta);
        player_pos.y += player_speed * sin(player_theta);
    }
    if (IsKeyDown(KEY_S))
    {
        player_pos.x -= player_speed * cos(player_theta);
        player_pos.y -= player_speed * sin(player_theta);
    }
    if (IsKeyDown(KEY_A))
    {
        player_pos.x += player_speed * cos(player_theta + PI/2);
        player_pos.y += player_speed * sin(player_theta + PI/2);
    }
    if (IsKeyDown(KEY_D))
    {
        player_pos.x += player_speed * cos(player_theta - PI/2);
        player_pos.y += player_speed * sin(player_theta - PI/2);
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) player_speed = 2.0f;
    else player_speed = 0.05f;

    if (IsKeyDown(KEY_R)) player_pos.z += 0.1f;
    if (IsKeyDown(KEY_F)) player_pos.z -= 0.1f;

    if (IsKeyDown(KEY_SPACE))
    {
        if (player_grounded)
        {
            player_jumped = true;
            player_grounded = false;
        }
    }
    update_player_BB();
}


void update_input()
{
    update_mouse();
    update_player_controls();
}

