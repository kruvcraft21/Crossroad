#include "traffic_sign.h"

// Конструктор класса Traffic_sign принимает путь к файлу изображения и позицию знака на экране.
Traffic_sign::Traffic_sign(const char *filepath, Vector2 pos)
{
    // Загружаем изображение из файла по указанному пути и сохраняем его
    // в переменную класса image, используя функцию LoadTexture из библиотеки Raylib.
    image = LoadTexture(filepath);
    
    // Сохраняем позицию знака на экране.
    position = pos;
}

// Метод Draw класса Traffic_sign отвечает за отрисовку знака на экране.
void Traffic_sign::Draw()
{
    // Используем функцию DrawTextureV из библиотеки Raylib для отрисовки изображения знака на экране
    // на указанной позиции (position).
    DrawTextureV(image, position, WHITE);
}