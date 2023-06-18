#pragma once
#include "road.h"
#include "car.h"
#include "traffic_sign.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Максимальное количество машин на дороге
constexpr int MAX_CAR = 10;
// Максимальное количество специальных машин на дороге
constexpr int MAX_SPEC_CAR = 3;

class Road_Controller
{
private:
    map<string, Road> road_collection; // Коллекция объектов дорог
    vector<Simple_Car> simple_cars; // Массив простых машин
    vector<Special_Car> spec_cars; // Массив специальных машин
    vector<Traffic_sign> traffic_signs; // Коллекция знаков дорожного движения

public:
    // Конструкторы и методы для управления дорогой и машинами на ней
    Road_Controller();
    void Start();
    void AddCars();
    void AddSimpleCar(Simple_Car &car);
    void AddSpecCar(Special_Car &car);
    bool CheckCar(Vector2 &pos);
    vector<Simple_Car>& get_simple_cars() { return simple_cars; } // Геттер для простых машин
    vector<Special_Car>& get_spec_cars() { return spec_cars; } // Геттер для специальных машин
    // Метод для создания и получения единственного экземпляра контроллера
    static Road_Controller& getInstance() {
        static Road_Controller instance;
        return instance;
    }    
};