#include "Meteor.h"

Meteor::Meteor() {
    position = { 0, 0 };
    speed = { 0, 0 };
    radius = 0;
    active = false;
    color = LIGHTGRAY;
}

void Meteor::Init(Vector2 pos, Vector2 spd, float r, Color clr) {
    position = pos;
    speed = spd;
    radius = r;
    color = clr;
    active = true;
}

void Meteor::Update(int screenWidth, int screenHeight) {
    if (!active) return;

    position.x += speed.x;
    position.y += speed.y;

    if (position.x > screenWidth + radius) position.x = -radius;
    else if (position.x < -radius) position.x = screenWidth + radius;

    if (position.y > screenHeight + radius) position.y = -radius;
    else if (position.y < -radius) position.y = screenHeight + radius;
}

void Meteor::Draw() const {
    if (active) DrawCircleV(position, radius, color);
    else DrawCircleV(position, radius, Fade(LIGHTGRAY, 0.3f));
}

bool Meteor::IsActive() const {
    return active;
}

void Meteor::Deactivate() {
    active = false;
}

Vector2 Meteor::GetPosition() const {
    return position;
}

Vector2 Meteor::GetSpeed() const {
    return speed;
}

float Meteor::GetRadius() const {
    return radius;
}

void Meteor::SetPosition(Vector2 pos) {
    position = pos;
}

void Meteor::SetSpeed(Vector2 spd) {
    speed = spd;
}

void Meteor::SetActive(bool state) {
    active = state;
}

// Derived Classes

BigMeteor::BigMeteor() {
    Init({ 0, 0 }, { 0, 0 }, 40.0f, DARKBLUE);
}

MediumMeteor::MediumMeteor() {
    Init({ -100, -100 }, { 0, 0 }, 30.0f, BLUE);
    Deactivate();
}

SmallMeteor::SmallMeteor() {
    Init({ -100, -100 }, { 0, 0 }, 10.0f, SKYBLUE);
    Deactivate();
}
