#include <iostream>
#include "raylib.h"
#include "roadcontroller.h"

int main(void) {
    InitWindow(500, 500, "Crossroad");
    SetTargetFPS(60);
    Road_Controller road_controller;
    road_controller.Start();
    return 0;
}