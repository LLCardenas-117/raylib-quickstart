#include "Shoot.h"
#include <cmath>

#define PLAYER_SPEED 6.0f

Shoot::Shoot() {
    position = { 0, 0 };
    speed = { 0, 0 };
    radius = 2;
    lifeSpan = 0;
    active = false;
    rotation = 0;
    color = BLACK;
}

void Shoot::Fire(Vector2 pos, float rot, float speedScale) {
    position = pos;
    rotation = rot;
    speed.x = speedScale * sinf(rot * DEG2RAD) * PLAYER_SPEED;
    speed.y = speedScale * cosf(rot * DEG2RAD) * PLAYER_SPEED;
    active = true;
    lifeSpan = 0;
}

void Shoot::Update(int screenWidth, int screenHeight) {
    if (!active) return;

    position.x += speed.x;
    position.y -= speed.y;
    lifeSpan++;

    if (position.x < -radius || position.x > screenWidth + radius ||
        position.y < -radius || position.y > screenHeight + radius ||
        lifeSpan >= 60) {
        Deactivate();
    }
}

void Shoot::Draw() const {
    if (active) {
        DrawCircleV(position, radius, color);
    }
}

bool Shoot::IsActive() const {
    return active;
}

void Shoot::Deactivate() {
    active = false;
    position = { 0, 0 };
    speed = { 0, 0 };
    lifeSpan = 0;
}

Vector2 Shoot::GetPosition() const {
    return position;
}

float Shoot::GetRadius() const {
    return radius;
}

float Shoot::GetRotation() const {
    return rotation;
}
