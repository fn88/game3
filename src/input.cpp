#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "set_up.h"
#include "audio.h"


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
    if (IsMouseButtonPressed(0)) player.attack1 = true;
    if (IsMouseButtonPressed(1)) play_bg_music(); //PlaySoundMulti(bg_wind); 

    if (IsKeyDown(KEY_W))
    {
        player.pos.x += player.speed * cos(player.theta);
        player.pos.y += player.speed * sin(player.theta);
    }
    if (IsKeyDown(KEY_S))
    {
        player.pos.x -= player.speed * cos(player.theta);
        player.pos.y -= player.speed * sin(player.theta);
    }
    if (IsKeyDown(KEY_A))
    {
        player.pos.x += player.speed * cos(player.theta + PI/2);
        player.pos.y += player.speed * sin(player.theta + PI/2);
    }
    if (IsKeyDown(KEY_D))
    {
        player.pos.x += player.speed * cos(player.theta - PI/2);
        player.pos.y += player.speed * sin(player.theta - PI/2);
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) player.speed = 2.0f;
    else player.speed = 0.25f;

    if (IsKeyDown(KEY_R)) player.pos.z += 0.1f;
    if (IsKeyDown(KEY_F)) player.pos.z -= 0.1f;

    if (IsKeyDown(KEY_SPACE))
    {
        if (player.grounded)
        {
            player.jumped = true;
            player.grounded = false;
        }
    }
    update_player_BB();
}


void update_input()
{
    update_mouse();
    update_player_controls();
}

