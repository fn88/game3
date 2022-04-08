#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "models.h"

//void collisions(model_Obj models, 

void player_collisions()
{
    for (auto it = level_models.begin(); it < level_models.end(); it++)
    {
        if ((player_BB.max.x > (*it).BB.min.x) && (player_BB.min.x < (*it).BB.max.x))
        {
            if ((player_BB.max.y > (*it).BB.min.y) && (player_BB.min.y < (*it).BB.max.y))
            {
                if ((player_BB.max.z > (*it).BB.min.z) && (player_BB.min.z < (*it).BB.max.z + 0.1f)) // test for ground nearby
                {
                    player_grounded = true;
                    player_time_not_grounded = 0;
                    player_jumped = false;
                    break;
                }
            }
        }
        else player_grounded = false;
    }

    for (auto it = level_models.begin(); it < level_models.end(); it++)
    {
        if (CheckCollisionBoxes(player_BB, (*it).BB))
        {
            player_colliding = true;
            if (player_prev_BB.min.x > (*it).BB.max.x)  // check if player collides from +X direction
            {
                if ((player_BB.max.x > (*it).BB.min.x) && (player_BB.min.x < (*it).BB.max.x))
                {
                    if ((player_prev_BB.max.y > (*it).BB.min.y) && (player_prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_prev_BB.max.z > (*it).BB.min.z) && (player_prev_BB.min.z < (*it).BB.max.z))
                        {
                            player_pos.x = (*it).BB.max.x + (player_size.x/2 + 0.001f);
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
            if (player_prev_BB.max.x < (*it).BB.min.x)  // check if player collides from -X direction
            {
                if ((player_BB.max.x > (*it).BB.min.x) && (player_BB.min.x < (*it).BB.max.x))
                {
                    if ((player_prev_BB.max.y > (*it).BB.min.y) && (player_prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_prev_BB.max.z > (*it).BB.min.z) && (player_prev_BB.min.z < (*it).BB.max.z))
                        {
                            player_pos.x = (*it).BB.min.x - (player_size.x/2 + 0.001f);
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
            if (player_prev_BB.min.y > (*it).BB.max.y)  // check if player collides from +Y direction
            {
                if ((player_prev_BB.max.x > (*it).BB.min.x) && (player_prev_BB.min.x <= (*it).BB.max.x))
                {
                    if ((player_BB.max.y > (*it).BB.min.y) && (player_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_prev_BB.max.z > (*it).BB.min.z) && (player_prev_BB.min.z < (*it).BB.max.z))
                        {
                            player_pos.y = (*it).BB.max.y + (player_size.y/2 + 0.001f);
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
            if (player_prev_BB.max.y < (*it).BB.min.y)  // check if player collides from -Y direction
            {
                if ((player_prev_BB.max.x > (*it).BB.min.x) && (player_prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((player_BB.max.y > (*it).BB.min.y) && (player_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_prev_BB.max.z > (*it).BB.min.z) && (player_prev_BB.min.z < (*it).BB.max.z))
                        {
                            player_pos.y = (*it).BB.min.y - (player_size.y/2 + 0.001f);
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
            if (player_prev_BB.min.z > (*it).BB.max.z)  // check if player collides from +Z direction
            {
                if ((player_prev_BB.max.x > (*it).BB.min.x) && (player_prev_BB.min.x < (*it).BB.max.x))
                {
                    if ((player_prev_BB.max.y > (*it).BB.min.y) && (player_prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_BB.max.z > (*it).BB.min.z) && (player_BB.min.z < (*it).BB.max.z))
                        {
                            player_pos.z = (*it).BB.max.z + (player_size.z/2 + 0.001f);
                            player_grounded = true;
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
            if (player_prev_BB.max.z < (*it).BB.min.z)  // check if player collides from -Z direction
            {
                if ((player_BB.max.z > (*it).BB.min.z) && (player_BB.min.z < (*it).BB.max.z))
                {
                    if ((player_prev_BB.max.y > (*it).BB.min.y) && (player_prev_BB.min.y < (*it).BB.max.y))
                    {
                        if ((player_prev_BB.max.x > (*it).BB.min.x) && (player_prev_BB.min.x < (*it).BB.max.x)) 
                        {
                            player_pos.z = (*it).BB.min.z - (player_size.z/2 + 0.001f);
                            update_player_BB();
                            break;
                        }
                    }
                }
            }
        }
        else player_colliding = false;  
    }

}
/*void bullets_collisions()
{
    if(!bullets.empty())
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            if (abs((*it).pos.x) > LVL_SIZE_X || abs((*it).pos.z) > LVL_SIZE_Y || abs((*it).pos.y) > LVL_SIZE_Z) bullets.erase(it);

            for (auto it2 = level_models.begin(); it2 < level_models.end(); it2++)
            {
                if (boxCollideDetect((*it).pos, (*it).size, (*it2).pos, (*it2).size))
                {
                    bullets.erase(it);
                }
            }
        }
} */


void all_collisions()
{
    player_collisions();
    //bullets_collisions();
}



