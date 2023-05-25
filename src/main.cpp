#include <iostream>
#include "raylib.h"
#include "roadcontroller.h"

int main(void) {
    InitWindow(500, 500, "Crossroad");
    SetTargetFPS(60);
    Road_Controller::getInstance().Start();
    return 0;
}