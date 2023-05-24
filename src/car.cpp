#include "car.h"
#include <math.h>

Car::Car(Vector2 &dir, Vector2 &startpos) {
    direction = dir;
    pos = startpos;
    radiusH = abs(direction.x * 10);
    radiusV = abs(direction.y * 10);
    if (radiusH < 1) radiusH = 5;
    if (radiusV < 1) radiusV = 5;
}

void Car::Draw() {
    DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), radiusH, radiusV, color);
    DrawEllipseLines(static_cast<int>(pos.x), static_cast<int>(pos.y), radiusH, radiusV, BLACK);
}

Vector2 Car::get_pos() {
    return pos;
}

void Car::Run() {
    int speed = 2;
    pos.x += direction.x * speed;
    pos.y += direction.y * speed;
}

void Simple_Car::set_color() {
    int c = GetRandomValue(1, 3);
    switch (c)
    {
    case 1:
        color = RED;
        break;
    case 2:
        color = GREEN;
        break;
    case 3:
        color = ORANGE;
        break;
    
    default:
        color = BLACK;
        break;
    }
}

Simple_Car::Simple_Car(Vector2 &dir, Vector2 &startpos) : Car(dir, startpos) {
    set_color();
}

void Simple_Car::Drive(std::vector<Simple_Car> simple_cars, std::vector<Special_Car> spec_cars, Rectangle &center)
{
    
    Run();
}

void Special_Car::Drive(std::vector<Simple_Car> simple_cars, std::vector<Special_Car> spec_cars, Rectangle &center)
{
    Run();
}