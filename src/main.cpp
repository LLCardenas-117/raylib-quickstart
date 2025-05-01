#include "raylib.h"
#include "Player.h"
#include "Shoot.h"
#include "Meteor.h"

#include <cmath>
#include <vector>

#define MAX_BIG_METEORS     16
#define MAX_MEDIUM_METEORS  32
#define MAX_SMALL_METEORS   64
#define PLAYER_MAX_SHOOTS   50
#define METEOR_SPEED        2

int screenWidth = 1200;
int screenHeight = 800;

// Global game state
bool gameOver = false;
bool pause = false;
bool victory = false;
int destroyedMeteorsCount = 0;
int midMeteorsCount = 0;
int smallMeteorsCount = 0;
int scoreForDestroyedMeteors = 0;

Player player;
Shoot shoots[PLAYER_MAX_SHOOTS];
BigMeteor bigMeteors[MAX_BIG_METEORS];
MediumMeteor mediumMeteors[MAX_MEDIUM_METEORS];
SmallMeteor smallMeteors[MAX_SMALL_METEORS];

// Function declarations
void InitGame();
void UpdateGame();
void DrawGame();

int main() {
    InitWindow(screenWidth, screenHeight, "Asteroid Game - OOP");

    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) && gameOver) {
            InitGame();
            gameOver = false;
        }

        UpdateGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}

void InitGame() {
    gameOver = false;
    pause = false;
    victory = false;
    destroyedMeteorsCount = 0;
    scoreForDestroyedMeteors = 0;
    midMeteorsCount = 0;
    smallMeteorsCount = 0;

    player.Reset(screenWidth, screenHeight);

    for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
        shoots[i] = Shoot();
    }

    for (int i = 0; i < MAX_BIG_METEORS; i++) {
        int posx = GetRandomValue(0, screenWidth);
        int posy = GetRandomValue(0, screenHeight);

        while (posx > screenWidth / 2 - 150 && posx < screenWidth / 2 + 150)
            posx = GetRandomValue(0, screenWidth);
        while (posy > screenHeight / 2 - 150 && posy < screenHeight / 2 + 150)
            posy = GetRandomValue(0, screenHeight);

        Vector2 pos = { (float)posx, (float)posy };
        Vector2 spd = { 0, 0 };
        while (spd.x == 0 && spd.y == 0) {
            spd.x = (float)GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
            spd.y = (float)GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
        }

        bigMeteors[i] = BigMeteor();
        bigMeteors[i].SetPosition(pos);
        bigMeteors[i].SetSpeed(spd);
        bigMeteors[i].SetActive(true);
    }

    for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
        mediumMeteors[i] = MediumMeteor();
    }

    for (int i = 0; i < MAX_SMALL_METEORS; i++) {
        smallMeteors[i] = SmallMeteor();
    }
}

void UpdateGame() {
    if (!gameOver) {
        if (IsKeyPressed(KEY_P)) pause = !pause;
        if (!pause) {
            player.Update(screenWidth, screenHeight);

            if (IsKeyPressed(KEY_SPACE)) {
                for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                    if (!shoots[i].IsActive()) {
                        float rot = player.GetRotation();
                        Vector2 pos = {
                            player.GetPosition().x + sinf(rot * DEG2RAD) * 20,
                            player.GetPosition().y - cosf(rot * DEG2RAD) * 20
                        };
                        shoots[i].Fire(pos, rot, 1.5f);
                        break;
                    }
                }
            }

            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                shoots[i].Update(screenWidth, screenHeight);
            }

            for (int i = 0; i < MAX_BIG_METEORS; i++) bigMeteors[i].Update(screenWidth, screenHeight);
            for (int i = 0; i < MAX_MEDIUM_METEORS; i++) mediumMeteors[i].Update(screenWidth, screenHeight);
            for (int i = 0; i < MAX_SMALL_METEORS; i++) smallMeteors[i].Update(screenWidth, screenHeight);

            // Collision: Player vs Meteors
            Vector3 collider = player.GetCollider();
            for (int i = 0; i < MAX_BIG_METEORS; i++) {
                if (bigMeteors[i].IsActive() &&
                    CheckCollisionCircles({ collider.x, collider.y }, collider.z,
                        bigMeteors[i].GetPosition(), bigMeteors[i].GetRadius())) {
                    gameOver = true;
                }
            }
            for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
                if (mediumMeteors[i].IsActive() &&
                    CheckCollisionCircles({ collider.x, collider.y }, collider.z,
                        mediumMeteors[i].GetPosition(), mediumMeteors[i].GetRadius())) {
                    gameOver = true;
                }
            }
            for (int i = 0; i < MAX_SMALL_METEORS; i++) {
                if (smallMeteors[i].IsActive() &&
                    CheckCollisionCircles({ collider.x, collider.y }, collider.z,
                        smallMeteors[i].GetPosition(), smallMeteors[i].GetRadius())) {
                    gameOver = true;
                }
            }

            // Collision: Shoots vs Meteors
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
                if (!shoots[i].IsActive()) continue;

                Vector2 sPos = shoots[i].GetPosition();
                float sRad = shoots[i].GetRadius();
                float rot = shoots[i].GetRotation();

                for (int a = 0; a < MAX_BIG_METEORS; a++) {
                    if (bigMeteors[a].IsActive() &&
                        CheckCollisionCircles(sPos, sRad, bigMeteors[a].GetPosition(), bigMeteors[a].GetRadius())) {

                        bigMeteors[a].Deactivate();
                        shoots[i].Deactivate();
                        destroyedMeteorsCount++;
                        scoreForDestroyedMeteors += 1;

                        for (int j = 0; j < 2 && midMeteorsCount < MAX_MEDIUM_METEORS; j++) {
                            mediumMeteors[midMeteorsCount].SetPosition(bigMeteors[a].GetPosition());
                            float dir = (midMeteorsCount % 2 == 0) ? -1 : 1;
                            mediumMeteors[midMeteorsCount].SetSpeed({
                                cosf(rot * DEG2RAD) * METEOR_SPEED * dir,
                                sinf(rot * DEG2RAD) * METEOR_SPEED * dir
                                });
                            mediumMeteors[midMeteorsCount].SetActive(true);
                            midMeteorsCount++;
                        }
                        break;
                    }
                }

                for (int b = 0; b < MAX_MEDIUM_METEORS; b++) {
                    if (mediumMeteors[b].IsActive() &&
                        CheckCollisionCircles(sPos, sRad, mediumMeteors[b].GetPosition(), mediumMeteors[b].GetRadius())) {

                        mediumMeteors[b].Deactivate();
                        shoots[i].Deactivate();
                        destroyedMeteorsCount++;
                        scoreForDestroyedMeteors += 3;

                        for (int j = 0; j < 2 && smallMeteorsCount < MAX_SMALL_METEORS; j++) {
                            smallMeteors[smallMeteorsCount].SetPosition(mediumMeteors[b].GetPosition());
                            float dir = (smallMeteorsCount % 2 == 0) ? -1 : 1;
                            smallMeteors[smallMeteorsCount].SetSpeed({
                                cosf(rot * DEG2RAD) * METEOR_SPEED * dir,
                                sinf(rot * DEG2RAD) * METEOR_SPEED * dir
                                });
                            smallMeteors[smallMeteorsCount].SetActive(true);
                            smallMeteorsCount++;
                        }
                        break;
                    }
                }

                for (int c = 0; c < MAX_SMALL_METEORS; c++) {
                    if (smallMeteors[c].IsActive() &&
                        CheckCollisionCircles(sPos, sRad, smallMeteors[c].GetPosition(), smallMeteors[c].GetRadius())) {

                        smallMeteors[c].Deactivate();
                        shoots[i].Deactivate();
                        destroyedMeteorsCount++;
                        scoreForDestroyedMeteors += 5;
                        break;
                    }
                }
            }

            if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS) {
                victory = true;
            }
        }
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameOver) {
        player.Draw();

        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) shoots[i].Draw();
        for (int i = 0; i < MAX_BIG_METEORS; i++) bigMeteors[i].Draw();
        for (int i = 0; i < MAX_MEDIUM_METEORS; i++) mediumMeteors[i].Draw();
        for (int i = 0; i < MAX_SMALL_METEORS; i++) smallMeteors[i].Draw();

        DrawText(TextFormat("Score: %08i", scoreForDestroyedMeteors), 10, 10, 30, DARKBLUE);

        if (pause) DrawText("PAUSED", screenWidth / 2 - 50, screenHeight / 2, 40, GRAY);
        if (victory) DrawText("VICTORY!", screenWidth / 2 - 80, screenHeight / 2, 40, GREEN);
    }
    else {
        DrawText(TextFormat("Score: %08i", scoreForDestroyedMeteors), screenWidth / 2 - 100, screenHeight / 2 - 40, 30, RED);
        DrawText("PRESS [ENTER] TO PLAY AGAIN", screenWidth / 2 - 150, screenHeight / 2, 20, DARKGRAY);
    }

    EndDrawing();
}
