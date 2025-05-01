#pragma once

#ifndef METEOR_H
#define METEOR_H

#include "raylib.h"

class Meteor {
protected:
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;

public:
    Meteor();
    virtual ~Meteor() = default;

    virtual void Init(Vector2 pos, Vector2 spd, float r, Color clr);
    virtual void Update(int screenWidth, int screenHeight);
    virtual void Draw() const;

    bool IsActive() const;
    void Deactivate();

    Vector2 GetPosition() const;
    Vector2 GetSpeed() const;
    float GetRadius() const;
    void SetPosition(Vector2 pos);
    void SetSpeed(Vector2 spd);
    void SetActive(bool state);
};

class BigMeteor : public Meteor {
public:
    BigMeteor();
};

class MediumMeteor : public Meteor {
public:
    MediumMeteor();
};

class SmallMeteor : public Meteor {
public:
    SmallMeteor();
};

#endif

