#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    float shipHeight;
    Vector3 collider;
    Color color;

public:
    Player();
    void Update(int screenWidth, int screenHeight);
    void Draw() const;
    Vector3 GetCollider() const;
    Vector2 GetPosition() const;
    float GetRotation() const;
    void Reset(int screenWidth, int screenHeight);
};

#endif
