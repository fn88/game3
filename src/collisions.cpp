#include "collisions.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "models.h"


void player_collisions()
{
    collisions(ptr_tree_models, ptr_player);
    collisions(ptr_level_models, ptr_player);
}


void collisions(std::vector<model_Obj> * models, entity_Obj * entity)
{
    for (auto it = (*models).begin(); it < (*models).end(); it++)
    {
        if (((*entity).BB.max.x > (*it).BB.min.x) && ((*entity).BB.min.x < (*it).BB.max.x))
        {
            if (((*entity).BB.max.y > (*it).BB.min.y) && ((*entity).BB.min.y < (*it).BB.max.y))
            {
                if (((*entity).BB.max.z > (*it).BB.min.z) && ((*entity).BB.min.z < (*it).BB.max.z + 0.1f)) // test for ground nearby
                {
                    (*entity).grounded = true;
                    (*entity).time_not_grounded = 0;
                    (*entity).jumped = false;
                    break;
                }
            }
        }
        else (*entity).grounded = false;
    }

    for (auto it = (*models).begin(); it < (*models).end(); it++)
    {
        if (CheckCollisionBoxes((*entity).BB, (*it).BB))
        {
            player.colliding = true;
            if ((*entity).prev_BB.min.x > (*it).BB.max.x)  // check if player collides from +X direction
            {
                if (((*entity).BB.max.x > (*it).BB.min.x) && ((*entity).BB.min.x < (*it).BB.max.x))
                {
                    if (((*entity).prev_BB.max.y > (*it).BB.min.y) && ((*entity).prev_BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).prev_BB.max.z > (*it).BB.min.z) && ((*entity).prev_BB.min.z < (*it).BB.max.z))
                        {
                            (*entity).pos.x = (*it).BB.max.x + ((*entity).size.x/2 + 0.001f);
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
            if ((*entity).prev_BB.max.x < (*it).BB.min.x)  // check if player collides from -X direction
            {
                if (((*entity).BB.max.x > (*it).BB.min.x) && ((*entity).BB.min.x < (*it).BB.max.x))
                {
                    if (((*entity).prev_BB.max.y > (*it).BB.min.y) && ((*entity).prev_BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).prev_BB.max.z > (*it).BB.min.z) && ((*entity).prev_BB.min.z < (*it).BB.max.z))
                        {
                            (*entity).pos.x = (*it).BB.min.x - ((*entity).size.x/2 + 0.001f);
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
            if ((*entity).prev_BB.min.y > (*it).BB.max.y)  // check if player collides from +Y direction
            {
                if (((*entity).prev_BB.max.x > (*it).BB.min.x) && ((*entity).prev_BB.min.x <= (*it).BB.max.x))
                {
                    if (((*entity).BB.max.y > (*it).BB.min.y) && ((*entity).BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).prev_BB.max.z > (*it).BB.min.z) && ((*entity).prev_BB.min.z < (*it).BB.max.z))
                        {
                            (*entity).pos.y = (*it).BB.max.y + ((*entity).size.y/2 + 0.001f);
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
            if ((*entity).prev_BB.max.y < (*it).BB.min.y)  // check if player collides from -Y direction
            {
                if (((*entity).prev_BB.max.x > (*it).BB.min.x) && ((*entity).prev_BB.min.x < (*it).BB.max.x))
                {
                    if (((*entity).BB.max.y > (*it).BB.min.y) && ((*entity).BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).prev_BB.max.z > (*it).BB.min.z) && ((*entity).prev_BB.min.z < (*it).BB.max.z))
                        {
                            (*entity).pos.y = (*it).BB.min.y - ((*entity).size.y/2 + 0.001f);
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
            if ((*entity).prev_BB.min.z > (*it).BB.max.z)  // check if player collides from +Z direction
            {
                if (((*entity).prev_BB.max.x > (*it).BB.min.x) && ((*entity).prev_BB.min.x < (*it).BB.max.x))
                {
                    if (((*entity).prev_BB.max.y > (*it).BB.min.y) && ((*entity).prev_BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).BB.max.z > (*it).BB.min.z) && ((*entity).BB.min.z < (*it).BB.max.z))
                        {
                            (*entity).pos.z = (*it).BB.max.z + ((*entity).size.z/2 + 0.001f);
                            (*entity).grounded = true;
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
            if ((*entity).prev_BB.max.z < (*it).BB.min.z)  // check if player collides from -Z direction
            {
                if (((*entity).BB.max.z > (*it).BB.min.z) && ((*entity).BB.min.z < (*it).BB.max.z))
                {
                    if (((*entity).prev_BB.max.y > (*it).BB.min.y) && ((*entity).prev_BB.min.y < (*it).BB.max.y))
                    {
                        if (((*entity).prev_BB.max.x > (*it).BB.min.x) && ((*entity).prev_BB.min.x < (*it).BB.max.x)) 
                        {
                            (*entity).pos.z = (*it).BB.min.z - ((*entity).size.z/2 + 0.001f);
                            (*entity).BB = update_BB_pos((*entity).BB, (*entity).size, (*entity).pos);
                            break;
                        }
                    }
                }
            }
        }
        else player.colliding = false;
    }
}




