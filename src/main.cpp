#include <iostream>
#include "raylib.h"
#include "roadcontroller.h"

int main(void) {
    // Инициализируем окно с размером 500x500 и названием "Crossroad".
    InitWindow(500, 500, "Crossroad");
    // Устанавливаем желаемый FPS в 60 кадров в секунду.
    SetTargetFPS(60);
    // Запускаем контроллер дороги и перекрестка.
    Road_Controller::getInstance().Start();
    // Завершаем функцию main и возвращаем 0, чтобы указать, что программа завершилась без ошибок.
    return 0;
}