#include "roadcontroller.h"

Road_Controller::Road_Controller() {
    // Draw road
    Rectangle left_rect = {0, 200, 200, 100};
    Vector2 left_pos = {0, 0};
    // Draw mark
    Vector2 left_b = {0, 250},  left_e = {200, 250};
    Mark left_mark = {left_b, left_e};
    road_left = make_unique<Road>(left_rect, left_pos, left_mark);

    Rectangle up_rect = {200, 0, 100, 200};
    Vector2 up_pos = {0, 0};
    Vector2 up_b = {250, 0},    up_e = {250, 200};
    Mark up_mark = {up_b, up_e};
    road_up = make_unique<Road>(up_rect, up_pos, up_mark);

    Rectangle button_rect = {200, 300, 100, 200};
    Vector2 button_pos = {0, 0};
    Vector2 button_b = {250, 300},  button_e = {250, 500};
    Mark button_mark = {button_b, button_e};
    road_button = make_unique<Road>(button_rect, button_pos, button_mark);

    Rectangle right_rect = {300, 200, 200, 100};
    Vector2 right_pos = {0, 0};
    Vector2 right_b = {300, 250},   right_e = {500, 250};
    Mark right_mark = {right_b, right_e};
    road_right = make_unique<Road>(right_rect, right_pos, right_mark);

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
            road_button->Draw();
            road_right->Draw();
            road_center->Draw();

            DrawFPS(10, 10);
        EndDrawing();
    }
    
}