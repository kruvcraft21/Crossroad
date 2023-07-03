#pragma once

#include "raylib.h"
#include "road.h"
#include <vector>
#include <map>
#include <string>
#include <array>

// Вычисление необходимых констант при компиляции
constexpr float DEGTORAD50 = 50 * DEG2RAD;
constexpr float DEGTORAD45 = 45 * DEG2RAD;

class Special_Car;
class Simple_Car;

// Класс, представляющий машину
class Car 
{
protected:
    Vector2 direction; // направление движения
    float radiusH = 5; // горизонтальный радиус
    float radiusV = 5; // вертикальный радиус
    int speed = 2; // скорость
    Vector2 pos; // позиция
    Color color = BLACK; // цвет
    std::map<std::string, std::array<Vector2, 3>> overview_car; // Треугольники обзора

protected:
    Car(Vector2& dir, Vector2& startpos); // конструктор
    void Run(); // метод для движения машины 

public:
    Car() = delete;
    void Draw(); // метод для отрисовки машины
    Vector2& get_pos(); // метод для получения позиции машины
    Vector2 get_dir() { return direction; }; // метод для получения направления движения машины
};

// Класс, наследующий от класса Car и представляющий простую машину
class Simple_Car : public Car 
{
private:
    void set_color(); // Метод устанавливает случайный цвет для автомобиля

public:
    void Drive(); // метод для движения простой машины
    Simple_Car(Vector2& dir, Vector2& startpos); // конструктор простой машины
};

// Класс, наследующий от класса Car и представляющий специальную машину
class Special_Car : public Car
{
public:
    Special_Car(Vector2& dir, Vector2& startpos); // конструктор специальной машины
    void Drive(); // метод для движения специальной машины
};