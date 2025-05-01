#include "Player.h"
#include <cmath>

#define PLAYER_BASE_SIZE 45.0f
#define PLAYER_SPEED 6.0f

Player::Player() {
    shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);
    position = { 0, 0 };
    speed = { 0, 0 };
    acceleration = 0;
    rotation = 0;
    collider = { 0, 0, 12 };
    color = LIGHTGRAY;
}

void Player::Reset(int screenWidth, int screenHeight) {
    position = { (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
    speed = { 0, 0 };
    acceleration = 0;
    rotation = 0;
    collider = { position.x, position.y, 12 };
}

void Player::Update(int screenWidth, int screenHeight) {
    // Rotation
    if (IsKeyDown(KEY_LEFT)) rotation -= 2.5f;
    if (IsKeyDown(KEY_RIGHT)) rotation += 2.5f;

    // Acceleration
    speed.x = sinf(rotation * DEG2RAD) * PLAYER_SPEED;
    speed.y = cosf(rotation * DEG2RAD) * PLAYER_SPEED;

    if (IsKeyDown(KEY_UP)) {
        if (acceleration < 1) acceleration += 0.04f;
    }
    else {
        if (acceleration > 0) acceleration -= 0.02f;
        else acceleration = 0;
    }

    if (IsKeyDown(KEY_DOWN)) {
        if (acceleration > 0) acceleration -= 0.04f;
        else acceleration = 0;
    }

    // Movement
    position.x += speed.x * acceleration;
    position.y -= speed.y * acceleration;

    // Screen wrapping
    if (position.x > screenWidth + shipHeight) position.x = -shipHeight;
    else if (position.x < -shipHeight) position.x = screenWidth + shipHeight;

    if (position.y > screenHeight + shipHeight) position.y = -shipHeight;
    else if (position.y < -shipHeight) position.y = screenHeight + shipHeight;

    // Collider update
    collider = {
        position.x + sin(rotation * DEG2RAD) * (shipHeight / 2.5f),
        position.y - cos(rotation * DEG2RAD) * (shipHeight / 2.5f),
        12
    };
}

void Player::Draw() const {
    Vector2 v1 = { position.x + sinf(rotation * DEG2RAD) * shipHeight, position.y - cosf(rotation * DEG2RAD) * shipHeight };
    Vector2 v2 = { position.x - cosf(rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), position.y - sinf(rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };
    Vector2 v3 = { position.x + cosf(rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), position.y + sinf(rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };

    DrawTriangle(v1, v2, v3, MAROON);
}

Vector3 Player::GetCollider() const {
    return collider;
}

Vector2 Player::GetPosition() const {
    return position;
}

float Player::GetRotation() const {
    return rotation;
}
