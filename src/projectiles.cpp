#include "set_up.h"


std::vector<projectile_Obj> bullets {};


void update_bullets()
{
    if (!bullets.empty())
    {
                for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            (*it).pos.y += (*it).speed * cos((*it).phi) * sin((*it).theta);
            (*it).pos.z += (*it).speed * sin((*it).phi);
            (*it).pos.x += (*it).speed * cos((*it).phi) * cos((*it).theta);
        }
    }
}

void update_projectiles()  
{
    update_bullets();
}


