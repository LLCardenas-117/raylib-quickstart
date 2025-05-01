#pragma once

#ifndef SHOOT_H
#define SHOOT_H

#include "raylib.h"

class Shoot {
private:
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpan;
    bool active;
    Color color;

public:
    Shoot();
    void Fire(Vector2 pos, float rot, float speedScale);
    void Update(int screenWidth, int screenHeight);
    void Draw() const;
    bool IsActive() const;
    void Deactivate();
    Vector2 GetPosition() const;
    float GetRadius() const;
    float GetRotation() const;
};

#endif