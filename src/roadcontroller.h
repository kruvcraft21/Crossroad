#pragma once

#include "road.h"
#include "car.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;

constexpr int MAX_CAR = 10;

class Road_Controller{
private:
    map<string, Road> road_collection;
    vector<Simple_Car> simple_cars;
    vector<Special_Car> spec_cars;

public:
    Road_Controller();
    void Start();
    void AddCars();
    void AddSimpleCar(Simple_Car &car);
    bool CheckCar(Vector2 &pos);
};