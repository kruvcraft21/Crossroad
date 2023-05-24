#pragma once

#include "road.h"
#include "car.h"
#include <memory>
#include <vector>

using namespace std;

constexpr int MAX_CAR = 10;

class Road_Controller{
private:
    unique_ptr<Road> road_left = nullptr;
    unique_ptr<Road> road_up = nullptr;
    unique_ptr<Road> road_botton = nullptr;
    unique_ptr<Road> road_right = nullptr;
    unique_ptr<Road> road_center = nullptr;
    vector<Simple_Car> simple_cars;
    vector<Special_Car> spec_cars;

public:
    Road_Controller();
    void Start();
    void AddCars();
    void AddSimpleCar(Simple_Car &car);
    bool CheckCar(Vector2 &pos);
};