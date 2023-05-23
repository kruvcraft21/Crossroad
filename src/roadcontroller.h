#pragma once

#include "road.h"
#include <memory>

using namespace std;

class Road_Controller{
private:
    unique_ptr<Road> road_left = nullptr;
    unique_ptr<Road> road_up = nullptr;
    unique_ptr<Road> road_button = nullptr;
    unique_ptr<Road> road_right = nullptr;
    unique_ptr<Road> road_center = nullptr;

public:
    Road_Controller();
    void Start();
};