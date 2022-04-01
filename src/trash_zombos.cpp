#include "trash_zombos_header.h"
#include "audio.h"
#include "models.h"


float S_W = 1600.0f;
float S_H = 1000.0f;
float FPS = 60.0f;
float mouseSensitivity = 3.0f;
float camSpeed = 0.5f;
float theta = 0.0f;
float phi = 0.0f;

//------------------ p l a y e r --------------------------------------------------
Model playerModel;
moving_Obj player {
                    {10.0f, 6.0f, 10.0f},  // pos {x,y,z}
                    {3.0f, 3.0f, 3.0f},  // prev_pos
                    {1.0f, 2.0f, 1.0f},  // size
                    0.0f,                // theta
                    0.0f,                // prev_theta
                    0.0f,                // phi
                    0.0f,                // prev_phi
                    0.1f                 // speed
};

bool player_grounded;
bool player_jumped;
int player_time_not_grounded;
bool player_ramp_ejected; 
float player_ejected_theta;

Vector3 machine_gun_pos = {0};
                                /*player.pos.x + (cos(player.phi) * sin(player.theta)) * 10,
                                player.pos.y + sin(player.phi) * 10,
                                player.pos.z + (cos(player.phi) * cos(player.theta)) * 10  
};*/

//------------------------------------ e n e m y ------------------------------------
Model enemyModel;
moving_Obj enemy {
                    {10.0f, 3.0f, 10.0f},  // pos {x,y,z}
                    {10.0f, 3.0f, 10.0f},  // prev_pos
                    {2.0f, 4.0f, 2.0f},    // size
                    0.0f,                  // theta
                    0.0f,                  // prev_theta
                    0.0f,                  // phi
                    0.0f,                  // prev_phi
                    0.1f                   // speed
};
bool enemy_grounded;
bool enemy_jumped;
unsigned int enemy_time_not_grounded;

Vector3 enemy_move_poi = {float(GetRandomValue(-10, 10)), enemy.size.y/2, float(GetRandomValue(-10, 10))};
Vector3 enemy_aim_poi = {0};
float enemy_dir;

//---------------------------- b u l l e t s -------------------------------------------
Model bulletModel;
Model rocketModel;

//---------------------------- l e v e l -----------------------------------------------
Vector3 level_size = {400.0f, 400.0f, 400.0f};
Vector3 wallsSize[] = {
                        {200.0f, 1.0f, 200.0f},  // floor
                        {200.0f, 1.0f, 10.0f},   // z floor
                        {200.0f, 1.0f, 10.0f},   // -z floor
                        {41.0f, 8.0f, 41.0f},    // floating corner platform
                        {41.0f, 8.0f, 41.0f},    // floating corner platform
                        {41.0f, 8.0f, 41.0f},    // floating corner platform
                        {41.0f, 8.0f, 41.0f}     // floating corner platform
}; 
Vector3 wallsPos[] = {
                        {0.0f, -wallsSize[0].y/2, 0.0f},         // floor
                        {0.0f, 5.0f, 95.0f},                     // z floor
                        {0.0f, 5.0f, -95.0f},                    // -z floor
                        { 125.0f, -wallsSize[3].y/2,  125.0f},   // NE ramp platform
                        {-125.0f, -wallsSize[3].y/2,  125.0f},   // SE ramp platform
                        {-125.0f, -wallsSize[3].y/2, -125.0f},   // SW ramp platform
                        { 125.0f, -wallsSize[3].y/2, -125.0f}    // NW ramp platform
};
int numWalls = sizeof(wallsSize)/sizeof(wallsSize[0]);

ramp_Obj ramps[] = {
                    { false, {0.0f, 0.5f, 0.0f},        {6.0f, 2.0f, 6.0f}, 0, 1 },      // center testing one
                    { false, { 130.0f, 0.0f,  130.0f},  {6.0f, 2.0f, 6.0f}, -PI/2, 1 },      // NE
                    { false, {-130.0f, 0.0f,  130.0f},  {6.0f, 2.0f, 6.0f}, -PI, 1 },      // SE
                    { false, {-130.0f, 0.0f, -130.0f},  {6.0f, 2.0f, 6.0f}, -3*PI/2, 1 },      // SW
                    { false, { 130.0f, 0.0f, -130.0f},  {6.0f, 2.0f, 6.0f}, 0, 1 }       // NW
};
int numRamps = sizeof(ramps)/sizeof(ramps[0]);
 

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(S_W, S_H, "trash_zombos");
    SetMousePosition(S_W/2.0f, S_H/2.0f);
    HideCursor();
    SetTargetFPS(FPS);

    InitAudioDevice();
    load_Game_Sounds();
    
    cam = {0};
    cam.fovy = 40.0f;
    cam.up = {0.0f, 1.0f, 0.0f};
    cam.projection = CAMERA_PERSPECTIVE;
    cam.position = {player.pos.x, player.pos.y + player.size.y/2, player.pos.z};
    cam.target.x = player.pos.x + (cos(player.phi) * sin(player.theta));
    cam.target.y = player.pos.y + sin(player.phi);
    cam.target.z = player.pos.z + (cos(player.phi) * cos(player.theta));


    //--------------------------------- M o d e l s --------------------------------
    Model player_model = LoadModel("resources/player.obj");
    Texture2D player_model_texture = LoadTexture("resources/floor_texture.png");
    player_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_model_texture;

    Model enemy_model = LoadModel("resources/player.obj");
    Texture2D enemy_model_texture = LoadTexture("resources/floor_texture.png");
    enemy_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = enemy_model_texture;

    Model bullet_model = LoadModel("resources/bullet.obj");
    Texture2D bullet_model_texture = LoadTexture("resources/bullet_texture.png");
    bullet_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bullet_model_texture;

    Model rocket_model = LoadModel("resources/rocket2.obj");
    Texture2D rocket_model_texture = LoadTexture("resources/floor_texture.png");
    rocket_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = rocket_model_texture;

    Model cloud1_model = LoadModel("resources/cloud1.obj");
    Texture2D cloud1_model_texture = LoadTexture("resources/smoke1_texture.png");
    cloud1_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cloud1_model_texture;

    //------------
    Model machine_gun = LoadModel("resources/machine_gun.obj");
    Texture2D machine_gun_texture = LoadTexture("resources/floor_texture.png");
    machine_gun.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = machine_gun_texture;

    //----------------------------- L E V E L models -------------------------------
    Model level_floor_model = LoadModel("resources/level_floor.obj");
    Texture2D level_floor_texture = LoadTexture("resources/floor_texture.png");
    level_floor_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = level_floor_texture;

    Model floor_10x10_model = LoadModel("resources/floor_10x10.obj");
    Texture2D floor_10x10_model_texture = LoadTexture("resources/floor_texture.png");
    floor_10x10_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor_10x10_model_texture;

    Model floor_10x100_model = LoadModel("resources/floor_10x100.obj");
    Texture2D floor_10x100_model_texture = LoadTexture("resources/floor_texture.png");
    floor_10x100_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor_10x100_model_texture;

    Model floating_corner_platform_model_NE = LoadModel("resources/floating_corner_platform.obj"); 
    Texture2D floating_corner_platfrom_model_texture = LoadTexture("resources/floor_texture.png");
    floating_corner_platform_model_NE.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floating_corner_platfrom_model_texture;

    Model floating_corner_platform_model_SE = LoadModel("resources/floating_corner_platform.obj"); 
    floating_corner_platform_model_SE.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floating_corner_platfrom_model_texture;
    floating_corner_platform_model_SE.transform = MatrixRotateY(PI/2);

    Model floating_corner_platform_model_SW = LoadModel("resources/floating_corner_platform.obj"); 
    floating_corner_platform_model_SW.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floating_corner_platfrom_model_texture;
    floating_corner_platform_model_SW.transform = MatrixRotateY(PI);

    Model floating_corner_platform_model_NW = LoadModel("resources/floating_corner_platform.obj"); 
    floating_corner_platform_model_NW.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floating_corner_platfrom_model_texture;
    floating_corner_platform_model_NW.transform = MatrixRotateY(3*PI/2); 

//-----------------------------------------------------------------------------------------------------------
    Model ramp_model = LoadModel("resources/ramp2.iqm");
    Texture2D ramp_model_texture = LoadTexture("resources/smoke1_texture.png");
    SetMaterialTexture(&ramp_model.materials[0], MATERIAL_MAP_DIFFUSE, ramp_model_texture);
    ramp_model.transform = MatrixRotateX(PI/2);

    Model ramp_model_NE = LoadModel("resources/ramp2.iqm");
    SetMaterialTexture(&ramp_model_NE.materials[0], MATERIAL_MAP_DIFFUSE, ramp_model_texture);
    ramp_model_NE.transform = MatrixRotateX(PI/2);

    Model ramp_model_SE = LoadModel("resources/ramp2.iqm");
    SetMaterialTexture(&ramp_model_SE.materials[0], MATERIAL_MAP_DIFFUSE, ramp_model_texture);
    ramp_model_SE.transform = MatrixRotateX(PI/2);

    Model ramp_model_SW = LoadModel("resources/ramp2.iqm");
    SetMaterialTexture(&ramp_model_SW.materials[0], MATERIAL_MAP_DIFFUSE, ramp_model_texture);
    ramp_model_SW.transform = MatrixRotateX(PI/2);

    Model ramp_model_NW = LoadModel("resources/ramp2.iqm");
    SetMaterialTexture(&ramp_model_NW.materials[0], MATERIAL_MAP_DIFFUSE, ramp_model_texture);
    ramp_model_NW.transform = MatrixRotateX(PI/2);

    unsigned int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations("resources/ramp2.iqm", &animsCount);

    Model dir_arrows = LoadModel("resources/Yup_arrows.obj");

    Model wallsModels[] = {
                            level_floor_model,
                            floor_10x100_model,
                            floor_10x100_model,
                            floating_corner_platform_model_NE,
                            floating_corner_platform_model_SE, 
                            floating_corner_platform_model_SW,
                            floating_corner_platform_model_NW
    };

    Model rampsModels[] = {
                            ramp_model,
                            ramp_model_NE,
                            ramp_model_SE,
                            ramp_model_SW,
                            ramp_model_NW
    };


    while (!WindowShouldClose())
    {
        playerCollisions();
        enemyCollisions(); 
        rocketsCollisions();
        bulletsCollisions();

        for (int i = 0; i < numRamps; i++)
        {
            if (ramps[i].activated) 
            {
                UpdateModelAnimation(rampsModels[i], anims[0], ramps[i].frame);
                if (ramps[i].frame == 1) playSound(0);
            } 
        }
        if (IsMouseButtonPressed(1)) 
        {
            player_shoot_machine_gun();
            playSound(1);
        } 
    
        updateMouse();
        updatePlayer();
        updateEnemy();
        updateBullets();
        updateRockets();
        updateRamps();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(cam);

            DrawModel(player_model, player.pos, 1.0f, BLUE); 
            //machine_gun.transform = MatrixRotateXYZ({player.phi, -player.theta, 0.0f});
            //DrawModel(machine_gun, machine_gun_pos, 0.5f, RED);

            DrawModel(enemy_model, enemy.pos, 1.0f, GREEN);
            
            //---------- level -----------------------
            DrawModel(dir_arrows, {0.0f, 3.75f, 0.0f}, 5.0f, WHITE);

            for (int i = 0; i < numRamps; i++) 
            {
                DrawModelEx(rampsModels[i], ramps[i].pos, {0.0f, 1.0f, 0.0f}, RAD2DEG*ramps[i].theta, {1.0f, 1.0f, 1.0f}, GRAY);
            }

            for (int i = 0; i < 6; i++)
            {
                DrawModel(level_Models[i], wallsPos[i], 1.0f, BROWN);
            }
            
            //--------projectiles----------------------
            for (auto it = bullets.begin(); it < bullets.end(); it++)
            {   
                bullet_model.transform = MatrixRotateXYZ({(*it).phi, -(*it).theta, 0.0f});
                DrawModel(bullet_model, (*it).pos, 1.0f, YELLOW);
            }

            for (auto it = rockets.begin(); it < rockets.end(); it++)
            {
                if (!(*it).rocket_blown_up)
                {
                    rocket_model.transform = MatrixRotateXYZ({(*it).phi, -(*it).theta, 0.0f});
                    DrawModel(rocket_model, (*it).pos, 4.0f, WHITE);
                }
                for (auto it2 = (*it).trail_clouds.begin(); it2 < (*it).trail_clouds.end(); it2++)
                {
                    DrawModel(cloud1_model, (*it2).pos, (1.0f * (*it2).frame/FPS), ColorAlpha(WHITE, 1.0f - (*it2).frame/120.0f)); 
                }
            }

            EndMode3D();

            DrawFPS(10,10);
            DrawText(TextFormat("player_time_not_grounded: %02.i", player_time_not_grounded), 50, 140, 30, WHITE);
            DrawText(TextFormat("player.pos.x: %02.02f", player.pos.x), 50, 170, 30, WHITE);
            DrawText(TextFormat("player.pos.y: %02.02f", player.pos.y), 50, 200, 30, WHITE);
            DrawText(TextFormat("player.pos.z: %02.02f", player.pos.z), 50, 230, 30, WHITE);
            DrawText(TextFormat("numWalls: %02.i", numWalls), 50, 270, 30, WHITE);
            DrawText(TextFormat("player.theta: %02.02f", player.theta), 50, 300, 30, WHITE);
            DrawText(TextFormat("player.phi: %02.02f", player.phi), 50, 330, 30, WHITE);
            DrawText(TextFormat("player_ejected_theta: %02.02f", player_ejected_theta), 50, 360, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void updateMouse()
{
    mousePosX = (float)GetMouseX();
    mousePosY = (float)GetMouseY();
    mouseDistX = mouseSensitivity * (mousePosX - (S_W/2.0f));
    mouseDistY = mouseSensitivity * (mousePosY - (S_H/2.0f));
    SetMousePosition(S_W/2.0f, S_H/2.0f);

    theta = (float)mouseDistX/(S_W/2.0f) * (cam.fovy/2.0f) * DEG2RAD; 
    phi = (float)mouseDistY/(S_H/2.0f) * (cam.fovy/2.0f) * DEG2RAD;
}

//************************** P L A Y E R *****************************************************************************************************
void player_shoot_rocket()
{
    rockets.push_back(rocket_Obj{ false, player.pos, {1.0f, 1.0f, 1.0f}, player.theta, player.phi, 1.5f });
}
void player_shoot_machine_gun()
{
    bullets.push_back(moving_Obj{ player.pos, {0}, {0.02f, 0.02f, 1.2f}, player.theta, 0.0f, player.phi, 0.0f, 6.0f });
}
void updatePlayer()
{   
    player.prev_pos = player.pos;

    if (IsKeyPressed(KEY_Q)) 
    {
        player.pos = { 10.0f, 10.0f, 10.0f};
        player_time_not_grounded = 0;
    }
    if (IsMouseButtonPressed(0)) player_shoot_rocket();
    /*if (IsMouseButtonDown(1)) 
    {
        player_shoot_machine_gun();
        PlaySoundMulti(mg_shot_sound);
    } */
    /*if (isMouseButtonPressed(1))
    {
        animsFrameCounter++;
        UpdateModelAnimation(ramp_model, anims[0], animFrameCounter);
        if (animsFrameCounter >= anims[0].frameCount) animFrameCounter = 1;
    }*/


    if (IsKeyDown(KEY_W))
    {
        player.pos.x += player.speed * sin(player.theta);
        player.pos.z += player.speed * cos(player.theta);
    }
    if (IsKeyDown(KEY_S))
    {
        player.pos.x -= player.speed * sin(player.theta);
        player.pos.z -= player.speed * cos(player.theta);
    }
    if (IsKeyDown(KEY_A))
    {
        player.pos.x += player.speed * sin(player.theta + PI/2);
        player.pos.z += player.speed * cos(player.theta + PI/2);
    }
    if (IsKeyDown(KEY_D))
    {
        player.pos.x += player.speed * sin(player.theta - PI/2);
        player.pos.z += player.speed * cos(player.theta - PI/2);
    }

    if (!player_grounded)
    {
        if (player_ramp_ejected)
        {
            player.pos.y += 1.5f;
            player.pos.x += 2.5f * sin(player_ejected_theta);
            player.pos.z += 2.5f * cos(player_ejected_theta);
        }
        player_time_not_grounded += 1;
        player.pos.y += (-2.0) * pow(player_time_not_grounded/FPS, 2); // -9.8/2 ~ -5   (1/2 * gravity * t^2 kinematics eq.)
    }
    if (player_grounded)
    {
        player_ramp_ejected = false;
        player_jumped = false;
        player_time_not_grounded = 0;
        if (IsKeyPressed(KEY_SPACE)) 
        {
            player_jumped = true;
            player_grounded = false;
        }
    }
    if (player_jumped) player.pos.y += 0.5f;
   
    if (IsKeyDown(KEY_LEFT_CONTROL)) player.pos.y -= player.speed * 1.0f;
    if (IsKeyDown(KEY_LEFT_SHIFT)) player.speed = 1.0f;
    else player.speed = 0.2f;

    player.prev_theta = player.theta;                 // update prev angle to new
    player.prev_phi = player.phi;                     // update prev angle to new
    player.theta -= theta;                            // update view dir via mouse
    player.phi -= phi;                                // update view dir via mouse
    if (player.phi >  PI/2.2f) player.phi =  PI/2.2f;
    if (player.phi < -PI/2.2f) player.phi = -PI/2.2f;

    cam.position = player.pos;
    cam.target.x = player.pos.x + (cos(player.phi) * sin(player.theta));
    cam.target.y = player.pos.y + sin(player.phi);
    cam.target.z = player.pos.z + (cos(player.phi) * cos(player.theta));  

    machine_gun_pos = {
                        player.pos.x - sin(player.theta)/5 -2,//(cos(player.phi) * sin(player.theta - PI/4)) * 0.3f,
                        player.pos.y, //sin(player.phi) * 0.3f,
                        player.pos.z - cos(player.theta)/5 - 2 //(cos(player.phi) * cos(player.theta - PI/4)) * 0.3f
    };

}
void playerCollisions()
{
    for (int i = 0; i < numWalls; i++)
    {
        if (boxCollideDetect(player.pos, player.size, wallsPos[i], wallsSize[i]))
        {
            if (boxCollideDetect(Vector3{player.prev_pos.x, player.pos.y, player.prev_pos.z}, player.size, wallsPos[i], wallsSize[i])) // ----- y-axis 
            {
                if (wallsPos[i].y <= player.prev_pos.y) player.pos.y = (wallsPos[i].y + (wallsSize[i].y/2 + player.size.y/2 + 0.001f)); // player-wall face to face but 0.001 away to not collide
                else if (wallsPos[i].y > player.prev_pos.y) player.pos.y = (wallsPos[i].y - (wallsSize[i].y/2 + player.size.y/2 + 0.001f));
            }
            else if (boxCollideDetect(Vector3{player.pos.x, player.prev_pos.y, player.prev_pos.z}, player.size, wallsPos[i], wallsSize[i])) // ----- check if x-axis alone causes collision
            {
                if (wallsPos[i].x <= player.prev_pos.x) player.pos.x = (wallsPos[i].x + (wallsSize[i].x/2 + player.size.x/2 + 0.001f));  
                else if (wallsPos[i].x > player.prev_pos.x) player.pos.x = (wallsPos[i].x - (wallsSize[i].x/2 + player.size.x/2 + 0.001f));
            }
            else if (boxCollideDetect(Vector3{player.prev_pos.x, player.prev_pos.y, player.pos.z}, player.size, wallsPos[i], wallsSize[i]))  // ----- z-axis
            {
                if (wallsPos[i].z <= player.prev_pos.z) player.pos.z = (wallsPos[i].z + (wallsSize[i].z/2 + player.size.z/2 + 0.001f));
                else if (wallsPos[i].z > player.prev_pos.z) player.pos.z = (wallsPos[i].z - (wallsSize[i].z/2 + player.size.z/2 + 0.001f));
            }
            break;
        }
    } 

    for (int i = 0; i < numWalls; i++)
    {
        if (boxCollideDetect(Vector3{player.pos.x, player.pos.y - 0.05f, player.pos.z}, player.size, wallsPos[i], wallsSize[i])) 
        {
            player_grounded = true;
            break;
        }
        else player_grounded = false;
    }

    for (int i = 0;  i < numRamps; i++)
    {
        if (!ramps[i].activated)
        {
            if (boxCollideDetect(player.pos, player.size, ramps[i].pos, ramps[i].size)) 
            {
                ramps[i].activated = true;
                player_ramp_ejected = true;
                player_grounded = false;
                player_jumped = true;
                player_time_not_grounded = 0;
                player_ejected_theta = ramps[i].theta;
            }
        }
    }
 
}

//************************************************** e n e m y *******************************************************************************
void enemy_shoot_rocket(moving_Obj target)
{
    enemy.theta = atan2((target.pos.x - enemy.pos.x), (target.pos.z - enemy.pos.z)); 
    enemy.phi = atan2( (target.pos.y - enemy.pos.y), sqrt( pow((target.pos.z - enemy.pos.z), 2) + pow((target.pos.x - enemy.pos.x), 2) ) );

    rockets.push_back(rocket_Obj{ false, enemy.pos, {1.0f, 1.0f, 1.0f}, enemy.theta, enemy.phi, 2.0f });
    
}
void enemy_shoot(moving_Obj target)
{
    enemy.theta = atan2((target.pos.x - enemy.pos.x), (target.pos.z - enemy.pos.z)); 
    enemy.phi = atan2( (target.pos.y - enemy.pos.y), sqrt( pow((target.pos.z - enemy.pos.z), 2) + pow((target.pos.x - enemy.pos.x), 2) ) );

    //bullets.push_back(moving_Obj{ {enemy.pos}, {0}, {1.0f, 1.0f, 1.0f}, enemy.theta, enemy.prev_theta, enemy.phi, enemy.prev_phi, 6.0f });
}  
void updateEnemy()
{   
    enemy.prev_pos = enemy.pos;

    if (abs(enemy_move_poi.x - enemy.pos.x) < 0.1f && abs(enemy_move_poi.y - enemy.pos.y) < 0.1f && abs(enemy_move_poi.z - enemy.pos.z) < 0.1f)
    {
        enemy_move_poi = Vector3{ enemy.pos.x + float(GetRandomValue(-10, 10)), enemy.pos.y, enemy.pos.z + float(GetRandomValue(-10, 10)) };
        enemy_shoot_rocket(player);  //temp
    }
    enemy_dir = atan2((enemy_move_poi.x -  enemy.pos.x), (enemy_move_poi.z - enemy.pos.z));
    enemy.pos.x += enemy.speed * sin(enemy_dir);
    enemy.pos.z += enemy.speed * cos(enemy_dir);
    

    if (enemy_grounded)
    {
        enemy_jumped = false;
        enemy_time_not_grounded = 0;
        if (enemy_jumped) enemy_grounded = false;
    }
    if (enemy_jumped) enemy.pos.y += 0.5f;
    if (!enemy_grounded)
    {
        enemy_time_not_grounded += 1;
        enemy.pos.y += (-2.5) * pow(enemy_time_not_grounded/FPS, 2); // -9.8/2 ~ -5   (1/2 * gravity * t^2 kinematics eq.)
    }
}
void enemyCollisions()
{
    for (int i = 0; i < numWalls; i++)
    {
        if (boxCollideDetect(enemy.pos, enemy.size, wallsPos[i], wallsSize[i]))
        {
            if (boxCollideDetect(Vector3{enemy.prev_pos.x, enemy.pos.y, enemy.prev_pos.z}, enemy.size, wallsPos[i], wallsSize[i])) // ----- y-axis 
            {
                if (wallsPos[i].y <= enemy.prev_pos.y) enemy.pos.y = (wallsPos[i].y + (wallsSize[i].y/2 + enemy.size.y/2 + 0.001f)); // player-wall face to face but 0.001 away to not collide
                else if (wallsPos[i].y > enemy.prev_pos.y) enemy.pos.y = (wallsPos[i].y - (wallsSize[i].y/2 + enemy.size.y/2 + 0.001f));
            }
            else if (boxCollideDetect(Vector3{enemy.pos.x, enemy.prev_pos.y, enemy.prev_pos.z}, enemy.size, wallsPos[i], wallsSize[i])) // ----- check if x-axis alone causes collision
            {
                if (wallsPos[i].x <= enemy.prev_pos.x) enemy.pos.x = (wallsPos[i].x + (wallsSize[i].x/2 + enemy.size.x/2 + 0.001f));  
                else if (wallsPos[i].x > enemy.prev_pos.x) enemy.pos.x = (wallsPos[i].x - (wallsSize[i].x/2 + enemy.size.x/2 + 0.001f));
            }
            else if (boxCollideDetect(Vector3{enemy.prev_pos.x, enemy.prev_pos.y, enemy.pos.z}, enemy.size, wallsPos[i], wallsSize[i]))  // ----- z-axis
            {
                if (wallsPos[i].z <= enemy.prev_pos.z) enemy.pos.z = (wallsPos[i].z + (wallsSize[i].z/2 + enemy.size.z/2 + 0.001f));
                else if (wallsPos[i].z > enemy.prev_pos.z) enemy.pos.z = (wallsPos[i].z - (wallsSize[i].z/2 + enemy.size.z/2 + 0.001f));
            }
            break;
        }
    }
    for (int i = 0; i < numWalls; i++)
    {
        if (boxCollideDetect(Vector3{enemy.pos.x, enemy.pos.y - 0.05f, enemy.pos.z}, enemy.size, wallsPos[i], wallsSize[i])) 
        {
            enemy_grounded = true;
            break;
        }
        else enemy_grounded = false;
    }
}

//--------------------------- projectiles ----------------------------
void updateBullets()
{
    if(!bullets.empty())
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            (*it).pos.x += (*it).speed * cos((*it).phi) * sin((*it).theta);
            (*it).pos.y += (*it).speed * sin((*it).phi);
            (*it).pos.z += (*it).speed * cos((*it).phi) * cos((*it).theta);
        }
}
void bulletsCollisions()
{
    if(!bullets.empty())
        for (auto it = bullets.begin(); it < bullets.end(); it++)
        {
            if (abs((*it).pos.x) > level_size.x || abs((*it).pos.y) > level_size.y || abs((*it).pos.z) > level_size.z) bullets.erase(it);
            for (int w = 0; w < numWalls; w++)
                {
                    if (boxCollideDetect((*it).pos, (*it).size, wallsPos[w], wallsSize[w]))
                    {

                        bullets.erase(it);
                    }
                }
        }
}

void updateRockets()
{
    if (!rockets.empty())
        for (auto it = rockets.begin(); it < rockets.end(); it++)
        {
            if (!(*it).rocket_blown_up)
            {
                (*it).pos.x += (*it).speed * cos((*it).phi) * sin((*it).theta);
                (*it).pos.y += (*it).speed * sin((*it).phi);
                (*it).pos.z += (*it).speed * cos((*it).phi) * cos((*it).theta);
                float inc_x = (float(GetRandomValue(-5, 5))) / 55.0f;
                float inc_y = (float(GetRandomValue(-5, 5))) / 55.0f;
                float inc_z = (float(GetRandomValue(-5, 5))) / 55.0f;
                (*it).trail_clouds.push_back(anim_Obj{Vector3{(*it).pos.x + inc_x, (*it).pos.y + inc_y, (*it).pos.z + inc_z}, 1});
            }
            for (auto it2 = (*it).trail_clouds.begin(); it2 < (*it).trail_clouds.end(); it2++)
            {
                if ((*it2).frame > 120) (*it).trail_clouds.erase(it2);
                (*it2).frame += 1;
            }
            if ((*it).trail_clouds.empty()) rockets.erase(it);
        }
}
void rocketsCollisions()
{
    if(!rockets.empty())
        for (auto it = rockets.begin(); it < rockets.end(); it++)
        {
            if (abs((*it).pos.x) > level_size.x || abs((*it).pos.y) > level_size.y || abs((*it).pos.z) > level_size.z) 
                (*it).rocket_blown_up = true;
            for (int w = 0; w < numWalls; w++)
            {
                if (boxCollideDetect((*it).pos, (*it).size, wallsPos[w], wallsSize[w]))
                    (*it).rocket_blown_up = true;
            }
        }
}

//----------------------------------------- L E V E L ------------------------------------------
void updateRamps()
{
    for (int i = 0; i < numRamps; i++)
    {
        if (ramps[i].activated)
        {
            if (ramps[i].frame >= 120) 
            {
                ramps[i].activated = false;
                ramps[i].frame = 0;
            }
            ramps[i].frame++;
        }
    }
}
             