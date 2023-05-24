#include "roadcontroller.h"

Road_Controller::Road_Controller() {
    // Draw road
    Rectangle left_rect = {0, 200, 200, 100};
    Vector2 left_pos = {25, 275};
    // Draw mark
    Vector2 left_b = {0, 250},  left_e = {200, 250};
    Mark left_mark = {left_b, left_e};
    Vector2 left_dir = {1, 0};
    Road left(left_rect, left_pos, left_dir, left_mark);
    road_collection.insert(make_pair("left", left));

    Rectangle up_rect = {200, 0, 100, 200};
    Vector2 up_pos = {225, 25};
    Vector2 up_b = {250, 0},    up_e = {250, 200};
    Mark up_mark = {up_b, up_e};
    Vector2 up_dir = {0, 1};
    Road up(up_rect, up_pos, up_dir, up_mark);
    road_collection.insert(make_pair("up", up));

    Rectangle botton_rect = {200, 300, 100, 200};
    Vector2 botton_pos = {275, 475};
    Vector2 botton_b = {250, 300},  botton_e = {250, 500};
    Mark botton_mark = {botton_b, botton_e};
    Vector2 botton_dir = {0, -1};
    Road botton(botton_rect, botton_pos, botton_dir, botton_mark);
    road_collection.insert(make_pair("button", botton));

    Rectangle right_rect = {300, 200, 200, 100};
    Vector2 right_pos = {475, 225};
    Vector2 right_b = {300, 250},   right_e = {500, 250};
    Mark right_mark = {right_b, right_e};
    Vector2 right_dir = {-1, 0};
    Road right(right_rect, right_pos, right_dir, right_mark);
    road_collection.insert(make_pair("right", right));

    Rectangle center_rect = {200, 200, 100, 100};
    Vector2 center_pos = {0, 0};
    Road center(center_rect, center_pos);
    road_collection.insert(make_pair("center", center));
}

void Road_Controller::Start() {
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            for (auto road = road_collection.begin(); road != road_collection.end(); road++)
            {
                road->second.Draw();
            } 

            AddCars();

            for (int i = 0; i < simple_cars.size(); i++) {
                simple_cars[i].Draw();
                simple_cars[i].Drive(simple_cars, spec_cars);
                if (CheckCar(simple_cars[i].get_pos())) {
                    simple_cars.erase(simple_cars.begin() + i);
                }
            }

            DrawFPS(10, 10);
        EndDrawing();
    }
}

bool Road_Controller::CheckCar(Vector2 &pos) {
    bool a = pos.x > 500 || pos.x < 0;
    bool b = pos.y > 500 || pos.y < 0;
    return a || b;
}

void Road_Controller::AddCars()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousepos = GetMousePosition();
        if (CheckCollisionPointRec(mousepos, road_left->skelet))
        {
            Simple_Car car(road_left->direction, road_left->start);
            AddSimpleCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_up->skelet))
        {
            Simple_Car car(road_up->direction, road_up->start);
            AddSimpleCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_botton->skelet))
        {
            Simple_Car car(road_botton->direction, road_botton->start);
            AddSimpleCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_right->skelet))
        {
            Simple_Car car(road_right->direction, road_right->start);
            AddSimpleCar(car);
        }
    }
}

void Road_Controller::AddSimpleCar(Simple_Car &car) {
    if (simple_cars.size() <= MAX_CAR) {
        simple_cars.push_back(car);
    }
}