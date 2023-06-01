#pragma once

#include "raylib.h"

// Структура Mark представляет собой начальную и конечную позицию разметки 
typedef struct Mark {
    Vector2 begin_pos;
    Vector2 end_pos;
} Mark;

class Road {
private:
    Mark mark; // Разметка
    bool isMarking; // Имеет ли дорожный участок разметку
    Vector2 start; // Начальная позиция машины на участке
    Rectangle skelet; // Прямоугольник, описывающий границы дороги
    Vector2 direction = {0, 0}; // Направление движения по дороге

public:
    // Конструкторы для создания дороги с различными параметрами
    Road(Rectangle &rect, Vector2 &startpos);
    Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir);
    Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir, Mark& m);
    // Метод для получения начальной позиции машины
    Vector2& get_start_pos_car() { return start;}
    // Метод для получения направления движения по дороге
    Vector2& get_direction() { return direction;}
    // Метод для отрисовки дороги
    void Draw();
    // Метод для проверки пересечения с позицей
    bool CheckCollisionPosition(Vector2& pos);
};