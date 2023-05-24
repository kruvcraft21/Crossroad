#pragma once

#include "raylib.h"
#include <vector>

class Car
{
private:
    Vector2 direction;
    Rectangle form;

public:
    Vector2 pos;
    Car(Vector2 dir, Vector2 startpos);
    void Draw();
    void Run(std::vector<Car> cars);
};