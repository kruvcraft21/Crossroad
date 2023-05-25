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

public:
    Vector2 direction = {0, 0}; // Направление движения по дороге
    Vector2 start; // Начальная позиция машины участка
    Rectangle skelet; // Прямоугольник, описывающий границы дороги

public:
    // Конструкторы для создания дороги с различными параметрами
    Road(Rectangle &rect, Vector2 &startpos);
    Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir);
    Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir, Mark& m);
    // Метод для отрисовки дороги
    void Draw();
};