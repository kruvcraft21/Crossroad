#pragma once

#include "raylib.h"
#include "road.h"
#include <vector>

class Special_Car;
class Simple_Car;

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
    void Run();
    Vector2 get_pos();
    Vector2 get_dir() { return direction;};
};

class Simple_Car : public Car 
{
private:
    Rectangle final;
    void set_color();

public:
    void Drive(std::vector<Simple_Car> simple_cars, std::vector<Special_Car> spec_cars, Rectangle &center);
    Simple_Car(Vector2 &dir, Vector2 &startpos, Rectangle &finalpos);

};

class Special_Car : public Car
{
public:
    Special_Car(Vector2 &dir, Vector2 &startpos) : Car(dir, startpos) {}
    void Drive(std::vector<Simple_Car> simple_cars, std::vector<Special_Car> spec_cars, Rectangle &center);
};