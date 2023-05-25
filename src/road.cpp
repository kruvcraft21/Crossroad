#include "road.h"

// Конструктор, который принимает прямоугольник и начальную позицию машины
Road::Road(Rectangle &rect, Vector2 &startpos) {
    skelet = rect; // Присваиваем прямоугольнику значение rect
    start = startpos; // Присваиваем начальную позицию машины значение startpos
}

// Конструктор, который принимает прямоугольник, начальную позицию машины и направление движения по дороге
Road::Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir) : Road(rect, startpos)
{
    direction = dir; // Присваиваем направлению движения значение dir
}

// Конструктор, который принимает прямоугольник, начальную позицию машины, направление движения по дороге и разметку дороги
Road::Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir, Mark &m) : Road(rect, startpos, dir) {
    isMarking = true; // Устанавливаем флаг, что участок дороги имеет разметку
    mark = m; // Присваиваем разметке значение m
}

// Метод для отрисовки дороги и разметки, если она есть
void Road::Draw() {
    DrawRectangleRec(skelet, GRAY); // Отрисовываем прямоугольник дороги
    if (isMarking) { // Если на дороге есть разметка
        DrawLineV(mark.begin_pos, mark.end_pos, WHITE); // Отрисовываем разметку
    }
}