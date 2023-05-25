#include "car.h"
#include <math.h>
#include "roadcontroller.h"

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

Simple_Car::Simple_Car(Vector2 &dir, Vector2 &startpos, Rectangle &finalpos) : Car(dir, startpos) {
    set_color();
    final = finalpos;
}

void Simple_Car::Drive()
{
    auto controller = Road_Controller::getInstance();
    std::vector<Special_Car> spec_cars = controller.get_spec_cars();
    std::vector<Simple_Car> simple_cars = controller.get_simple_cars(); 
    bool saw_obstacle = false;
    float rotate = atan2f(direction.x, direction.y);
    Vector2 up_side = {
        pos.x + sinf(rotate) * 100,
        pos.y + cosf(rotate) * 100
    };
    Vector2 right_side = {
        pos.x + sinf(rotate - (60 * DEG2RAD)) * 110,
        pos.y + cosf(rotate - (60 * DEG2RAD)) * 110
    };
    Vector2 left_side = {
        pos.x + sinf(rotate + (60 * DEG2RAD)) * 110,
        pos.y + cosf(rotate + (60 * DEG2RAD)) * 110
    };

    Vector2 right_side_light = {
        pos.x + sinf(rotate - (60 * DEG2RAD)) * 50,
        pos.y + cosf(rotate - (60 * DEG2RAD)) * 50
    };
    Vector2 left_side_light = {
        pos.x + sinf(rotate + (60 * DEG2RAD)) * 50,
        pos.y + cosf(rotate + (60 * DEG2RAD)) * 50
    };

    for (int i = 0; i < simple_cars.size(); i++)
    {
        Vector2 position = simple_cars[i].get_pos();
        Vector2 dir = simple_cars[i].get_dir();
        if (direction.y == 0)
        {
            if (CheckCollisionPointTriangle(position, pos, right_side, left_side)
                && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
            {
                saw_obstacle = true;
            }
        }

        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light) 
            && (direction.x == dir.x && direction.y == dir.y))
        {
            saw_obstacle = true;
        }
    }
    
    for (int i = 0; i < spec_cars.size(); i++)
    {
        Vector2 position = spec_cars[i].get_pos();
        Vector2 dir = spec_cars[i].get_dir();
        if (CheckCollisionPointTriangle(position, pos, right_side, left_side)
            && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
        {
            saw_obstacle = true;
        }

        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light) 
            && (direction.x == dir.x && direction.y == dir.y))
        {
            saw_obstacle = true;
        }
    }
    

    if (!saw_obstacle) Run(); 
}

void Special_Car::Drive()
{
    Road_Controller controller = Road_Controller::getInstance();
    std::vector<Special_Car> spec_cars = controller.get_spec_cars();
    std::vector<Simple_Car> simple_cars = controller.get_simple_cars(); 

    bool saw_obstacle = false;
    float rotate = atan2f(direction.x, direction.y);
    Vector2 right_side_light = {
        pos.x + sinf(rotate - (60 * DEG2RAD)) * 50,
        pos.y + cosf(rotate - (60 * DEG2RAD)) * 50
    };
    Vector2 left_side_light = {
        pos.x + sinf(rotate + (60 * DEG2RAD)) * 50,
        pos.y + cosf(rotate + (60 * DEG2RAD)) * 50
    };

    for (int i = 0; i < spec_cars.size(); i++)
    {
        Vector2 position = spec_cars[i].get_pos();
        Vector2 dir = spec_cars[i].get_dir();

        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light) 
            && (direction.x == dir.x && direction.y == dir.y))
        {
            saw_obstacle = true;
        }
    }

    for (int i = 0; i < simple_cars.size(); i++)
    {
        Vector2 position = simple_cars[i].get_pos();
        Vector2 dir = simple_cars[i].get_dir();

        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light) 
            && (direction.x == dir.x && direction.y == dir.y))
        {
            saw_obstacle = true;
        }
    }

    if (!saw_obstacle) Run(); 
}