#pragma once
#include "road.h"
#include "car.h"
#include "traffic_sign.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;

constexpr int MAX_CAR = 10;
constexpr int MAX_SPEC_CAR = 3;

class Road_Controller
{
private:
    map<string, Road> road_collection;
    vector<Simple_Car> simple_cars;
    vector<Special_Car> spec_cars;
    map<string, Traffic_sign> traffic_signs;

public:
    Road_Controller();
    void Start();
    void AddCars();
    void AddSimpleCar(Simple_Car &car);
    void AddSpecCar(Special_Car &car);
    bool CheckCar(Vector2 &pos);
    vector<Simple_Car> get_simple_cars() {return simple_cars;}
    vector<Special_Car> get_spec_cars() {return spec_cars;}
    static Road_Controller& getInstance() {
        static Road_Controller  instance;
        return instance;
    }    
};