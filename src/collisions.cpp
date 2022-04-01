#include "set_up.h"


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

void player_collisions()
{
    if (!level_models.empty())
    {
        for (auto it = level_models.begin(); it < level_models.end(); it++)
        {
            if (boxCollideDetect(player_pos, player_size, (*it).pos, (*it).size))
            {
                if (boxCollideDetect(Vector3{player_prev_pos.x, player_prev_pos.y, player_pos.z}, player_size, (*it).pos, (*it).size)) // ----- z-axis 
                {
                    if ((*it).pos.z <= player_prev_pos.z) player_pos.z = ((*it).pos.z + ((*it).size.z/2 + player_size.z/2 + 0.001f)); // player-wall face to face but 0.001 away to not collide
                    else if ((*it).pos.z > player_prev_pos.z) player_pos.z = ((*it).pos.z - ((*it).size.z/2 + player_size.z/2 + 0.001f));
                }
                else if (boxCollideDetect(Vector3{player_pos.x, player_prev_pos.y, player_prev_pos.z}, player_size, (*it).pos, (*it).size)) // ----- check if x-axis alone causes collision
                {
                    if ((*it).pos.x <= player_prev_pos.x) player_pos.x = ((*it).pos.x + ((*it).size.x/2 + player_size.x/2 + 0.001f));  
                    else if ((*it).pos.x > player_prev_pos.x) player_pos.x = ((*it).pos.x - ((*it).size.x/2 + player_size.x/2 + 0.001f));
                }
                else if (boxCollideDetect(Vector3{player_prev_pos.x, player_pos.y, player_prev_pos.z}, player_size, (*it).pos, (*it).size))  // ----- y-axis
                {
                    if ((*it).pos.y <= player_prev_pos.y) player_pos.y = ((*it).pos.y + ((*it).size.y/2 + player_size.y/2 + 0.001f));
                    else if ((*it).pos.y > player_prev_pos.y) player_pos.y = ((*it).pos.y - ((*it).size.y/2 + player_size.y/2 + 0.001f));
                }
                break;
            }
        } 

        for (auto it = level_models.begin(); it < level_models.end(); it++)
        {
            if (boxCollideDetect(Vector3{player_pos.x, player_pos.y, player_pos.z - 0.05f}, player_size, (*it).pos, (*it).size)) 
            {
                player_grounded = true;
                break;
            }
            else player_grounded = false;
        }
    }
}

void bullets_collisions()
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
}


void all_collisions()
{
    player_collisions();
    bullets_collisions();
}



