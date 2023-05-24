#pragma once

#include "raylib.h"

class Car
{
private:
    Vector2 direction;

public:
    Vector2 pos;
    Car(Vector2 dir, Vector2 startpos);
};