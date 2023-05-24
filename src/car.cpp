#include "car.h"

Car::Car(Vector2 dir, Vector2 startpos) {
    direction = dir;
    pos = startpos;
    form = {pos.x - 10, pos.y - 5, 20, 10};
}

void Car::Draw() {
    DrawRectangleRounded(form, 5.0f, 6, RED);
}

void Car::Run(std::vector<Car> cars) {
    pos.x += direction.x * 5;
    pos.y += direction.y * 5;

    form.x += direction.x * 5;
    form.y += direction.y * 5;
}