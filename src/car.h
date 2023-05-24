#pragma once

#include "raylib.h"
#include <vector>

class Car
{
protected:
    Vector2 direction;
    float radiusH = 5;
    float radiusV = 5;
    int speed = 2;
    Vector2 pos;
    Color color = BLACK;

public:
    Car(Vector2 &dir, Vector2 &startpos);
    void Draw();
    void Run(std::vector<Car> cars);
};