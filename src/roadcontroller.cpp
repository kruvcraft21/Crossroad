#include "roadcontroller.h"

Road_Controller::Road_Controller() {
    // Draw road
    Rectangle left_rect = {0, 200, 200, 100};
    Vector2 left_pos = {25, 275};
    // Draw mark
    Vector2 left_b = {0, 250},  left_e = {200, 250};
    Mark left_mark = {left_b, left_e};
    Vector2 left_dir = {1, 0};
    road_left = make_unique<Road>(left_rect, left_pos, left_dir, left_mark);

    Rectangle up_rect = {200, 0, 100, 200};
    Vector2 up_pos = {225, 25};
    Vector2 up_b = {250, 0},    up_e = {250, 200};
    Mark up_mark = {up_b, up_e};
    Vector2 up_dir = {0, -1};
    road_up = make_unique<Road>(up_rect, up_pos, up_dir, up_mark);

    Rectangle botton_rect = {200, 300, 100, 200};
    Vector2 botton_pos = {275, 475};
    Vector2 botton_b = {250, 300},  botton_e = {250, 500};
    Mark botton_mark = {botton_b, botton_e};
    Vector2 botton_dir = {0, 1};
    road_botton = make_unique<Road>(botton_rect, botton_pos, botton_dir, botton_mark);

    Rectangle right_rect = {300, 200, 200, 100};
    Vector2 right_pos = {475, 225};
    Vector2 right_b = {300, 250},   right_e = {500, 250};
    Mark right_mark = {right_b, right_e};
    Vector2 right_dir = {-1, 0};
    road_right = make_unique<Road>(right_rect, right_pos, right_dir, right_mark);

    Rectangle center_rect = {200, 200, 100, 100};
    Vector2 center_pos = {0, 0};
    road_center = make_unique<Road>(center_rect, center_pos);
}

void Road_Controller::Start() {
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            road_left->Draw();
            road_up->Draw();
            road_botton->Draw();
            road_right->Draw();
            road_center->Draw();

            AddCars();

            for (int i = 0; i < cars.size(); i++) {
                cars[i].Draw();
            }

            DrawFPS(10, 10);
        EndDrawing();
    }
}

void Road_Controller::AddCars()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousepos = GetMousePosition();
        if (CheckCollisionPointRec(mousepos, road_left->skelet))
        {
            Car car(road_left->direction, road_left->start);
            AddCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_up->skelet))
        {
            Car car(road_up->direction, road_up->start);
            AddCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_botton->skelet))
        {
            Car car(road_botton->direction, road_botton->start);
            AddCar(car);
        }
        else if (CheckCollisionPointRec(mousepos, road_right->skelet))
        {
            Car car(road_right->direction, road_right->start);
            AddCar(car);
        }
    }
}

void Road_Controller::AddCar(Car &car) {
    if (cars.size() <= MAX_CAR) {
        cars.push_back(car);
    }
}