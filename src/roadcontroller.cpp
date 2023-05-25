#include "roadcontroller.h"

Road_Controller::Road_Controller() {
    // Draw road
    Rectangle left_rect = {0, 200, 200, 100};
    Vector2 left_pos = {25, 275};
    // Draw mark
    Vector2 left_b = {0, 250},  left_e = {200, 250};
    Mark left_mark = {left_b, left_e};
    // Direction
    Vector2 left_dir = {1, 0};
    // Final pos
    Rectangle left_final_pos = {150, 250, 50, 50};
    Road left(left_rect, left_pos, left_final_pos, left_dir, left_mark);
    road_collection.insert(make_pair("left", left));

    Rectangle up_rect = {200, 0, 100, 200};
    Vector2 up_pos = {225, 25};
    Vector2 up_b = {250, 0},    up_e = {250, 200};
    Mark up_mark = {up_b, up_e};
    Vector2 up_dir = {0, 1};
    Rectangle up_final_pos = {200, 150, 50, 50};
    Road up(up_rect, up_pos, up_final_pos, up_dir, up_mark);
    road_collection.insert(make_pair("up", up));

    Rectangle botton_rect = {200, 300, 100, 200};
    Vector2 botton_pos = {275, 475};
    Vector2 botton_b = {250, 300},  botton_e = {250, 500};
    Mark botton_mark = {botton_b, botton_e};
    Vector2 botton_dir = {0, -1};
    Rectangle botton_final_pos = {250, 300, 50, 50};
    Road botton(botton_rect, botton_pos, botton_final_pos, botton_dir, botton_mark);
    road_collection.insert(make_pair("button", botton));

    Rectangle right_rect = {300, 200, 200, 100};
    Vector2 right_pos = {475, 225};
    Vector2 right_b = {300, 250},   right_e = {500, 250};
    Mark right_mark = {right_b, right_e};
    Vector2 right_dir = {-1, 0};
    Rectangle right_final_pos = {300, 200, 50, 50};
    Road right(right_rect, right_pos, right_final_pos, right_dir, right_mark);
    road_collection.insert(make_pair("right", right));

    Rectangle center_rect = {200, 200, 100, 100};
    Vector2 center_pos = {0, 0};
    Road center(center_rect, center_pos);
    road_collection.insert(make_pair("center", center));

    traffic_signs.insert(make_pair("glavnaya", Traffic_sign("resources/glavnaya.png", {150, 150})));
    traffic_signs.insert(make_pair("glavnaya2", Traffic_sign("resources/glavnaya.png", {300, 300})));
    traffic_signs.insert(make_pair("neglavnaya2", Traffic_sign("resources/neglavnaya2.png", {150, 300})));
    traffic_signs.insert(make_pair("neglavnaya3", Traffic_sign("resources/neglavnaya3.png", {300, 150})));
}

void Road_Controller::Start() {
    Rectangle center = road_collection.find("center")->second.skelet;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            for (auto road = road_collection.begin(); road != road_collection.end(); road++)
            {
                road->second.Draw();
            } 

            for (auto traffic_sign = traffic_signs.begin(); traffic_sign != traffic_signs.end(); traffic_sign++)
            {
                traffic_sign->second.Draw();
            }

            AddCars();

            for (int i = 0; i < simple_cars.size(); i++) {
                simple_cars[i].Draw();
                simple_cars[i].Drive();
                if (CheckCar(simple_cars[i].get_pos())) 
                {
                    simple_cars.erase(simple_cars.begin() + i);
                }
            }

            for (int i = 0; i < spec_cars.size(); i++)
            {
                spec_cars[i].Draw();
                spec_cars[i].Drive();
                if (CheckCar(spec_cars[i].get_pos()))
                {
                    spec_cars.erase(spec_cars.begin() + i);
                }
            }
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
        for (auto road = road_collection.begin(); road != road_collection.end(); road++) {
            if (road->first != "center" && CheckCollisionPointRec(mousepos, road->second.skelet)) {
                Simple_Car car(road->second.direction, road->second.start, road->second.final);
                AddSimpleCar(car);
            }
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) 
    {
        Vector2 mousepos = GetMousePosition();
        for (auto road = road_collection.begin(); road != road_collection.end(); road++) {
            if (road->first != "center" && CheckCollisionPointRec(mousepos, road->second.skelet)) {
                Special_Car car(road->second.direction, road->second.start);
                AddSpecCar(car);
            }
        }
    }
}

void Road_Controller::AddSimpleCar(Simple_Car &car) {
    if (simple_cars.size() < MAX_CAR) {
        simple_cars.push_back(car);
    }
}

void Road_Controller::AddSpecCar(Special_Car &car)
{
    if (spec_cars.size() < MAX_SPEC_CAR)
    {
        spec_cars.push_back(car);
    }
}