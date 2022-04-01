#pragma once
#include "raylib.h"
#include "player.h"
#include "set_up.h"
#include "collisions.h"
#include "models.h"
#include <vector>
#include <cmath>


struct projectile_Obj {
                    Vector3 pos{};
                    Vector3 prev_pos{};
                    Vector3 size{};
                    float theta;
                    float prev_theta;
                    float phi;
                    float prev_phi;
                    float speed;
};

extern std::vector<projectile_Obj> bullets;


void update_bullets();

void update_projectiles();




