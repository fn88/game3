#pragma once
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <vector>
#include <cstdlib>
 
 
Camera cam;

float mousePosX;
float mousePosY;
float mouseDistX;
float mouseDistY;

void updateMouse();
void updatePlayer();
void updateEnemy();
void updateBullets();
void updateRockets();
void updateRamps();

void playerCollisions();
void enemyCollisions();
void bulletsCollisions();
void rocketsCollisions();

void player_shoot_machine_gun();


struct moving_Obj {
                    Vector3 pos{};
                    Vector3 prev_pos{};
                    Vector3 size{};
                    float theta;
                    float prev_theta;
                    float phi;
                    float prev_phi;
                    float speed;
};

struct anim_Obj { 
                Vector3 pos{};
                unsigned int frame;
};

struct rocket_Obj {
                        bool rocket_blown_up;
                        Vector3 pos{};
                        Vector3 size{};
                        float theta;
                        float phi;
                        float speed;
                        std::vector<anim_Obj> trail_clouds;
};

struct ramp_Obj {
                        bool activated;
                        Vector3 pos{};
                        Vector3 size{};
                        float theta;
                        unsigned int frame;
};


bool boxCollideDetect(Vector3 box_A_pos, Vector3 box_A_size, Vector3 box_B_pos, Vector3 box_B_size)
{
   return CheckCollisionBoxes(
                BoundingBox{Vector3{box_A_pos.x - box_A_size.x/2,
                                    box_A_pos.y - box_A_size.y/2,
                                    box_A_pos.z - box_A_size.z/2},
                            Vector3{box_A_pos.x + box_A_size.x/2,
                                    box_A_pos.y + box_A_size.y/2,
                                    box_A_pos.z + box_A_size.z/2}},
                BoundingBox{Vector3{box_B_pos.x - box_B_size.x/2,
                                    box_B_pos.y - box_B_size.y/2,
                                    box_B_pos.z - box_B_size.z/2},
                            Vector3{box_B_pos.x + box_B_size.x/2,
                                    box_B_pos.y + box_B_size.y/2,
                                    box_B_pos.z + box_B_size.z/2}});
}

std::vector<moving_Obj> bullets{};
std::vector<rocket_Obj> rockets{};

