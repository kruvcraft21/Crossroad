#include "car.h"
#include <math.h>
#include "roadcontroller.h"

// Конструктор инициализирует направление автомобиля, его начальную позицию и радиус эллипса, вычисленный на основе направления
Car::Car(Vector2 &dir, Vector2 &startpos) {
    direction = dir;
    pos = startpos;
    // Вычисление радиуса эллипса по горизонтальному и вертикальному направлениям
    radiusH = abs(direction.x * 10);
    radiusV = abs(direction.y * 10);
    // Если радиус по одному из направлений меньше 1, установить радиус в 5 пикселей
    if (radiusH < 1) radiusH = 5;
    if (radiusV < 1) radiusV = 5;
}

// Метод для отрисовки машины, рисует автомобиль в виде эллипса с заданной позицией и радиусом
void Car::Draw() {
    DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), radiusH, radiusV, color);
    DrawEllipseLines(static_cast<int>(pos.x), static_cast<int>(pos.y), radiusH, radiusV, BLACK);
}

// метод для получения позиции машины
Vector2 Car::get_pos() {
    return pos;
}

// Метод для движения машины, обновляет позицию автомобиля в соответствии с его направлением и скоростью
void Car::Run() {
    pos.x += direction.x * speed;
    pos.y += direction.y * speed;
}

// Метод устанавливает случайный цвет для автомобиля
void Simple_Car::set_color() {
    int c = GetRandomValue(1, 3);
    switch (c)
    {
    case 1:
        color = RED;
        break;
    case 2:
        color = GREEN;
        break;
    case 3:
        color = ORANGE;
        break;
    
    default:
        color = BLACK;
        break;
    }
}

// Конструктор Simple_Car вызывает конструктор Car и затем устанавливает случайный цвет для автомобиля
Simple_Car::Simple_Car(Vector2 &dir, Vector2 &startpos) : Car(dir, startpos) {
    set_color();
}

// Метод для движения простой машины
void Simple_Car::Drive()
{
    // Получаем экземпляр класса Road_Controller и векторы специальных и простых автомобилей
    auto controller = Road_Controller::getInstance();
    std::vector<Special_Car> spec_cars = controller.get_spec_cars();
    std::vector<Simple_Car> simple_cars = controller.get_simple_cars(); 

    // Флаг, который показывает, была ли обнаружена препятствие на пути автомобиля
    bool saw_obstacle = false;

    // Вычисляем угол поворота автомобиля
    float rotate = atan2f(direction.x, direction.y);

    // Вычисляем координаты вершин треугольника, определенного позицией и углом поворота автомобиля
    Vector2 right_side = {
        pos.x + sinf(rotate - (60 * DEG2RAD)) * 110,
        pos.y + cosf(rotate - (60 * DEG2RAD)) * 110
    };
    Vector2 left_side = {
        pos.x + sinf(rotate + (60 * DEG2RAD)) * 110,
        pos.y + cosf(rotate + (60 * DEG2RAD)) * 110
    };

    // Вычисляем координаты вершин треугольника, определенного позицией и углом поворота автомобиля
    Vector2 right_side_light = {
        pos.x + sinf(rotate - (45 * DEG2RAD)) * 50,
        pos.y + cosf(rotate - (45 * DEG2RAD)) * 50
    };
    Vector2 left_side_light = {
        pos.x + sinf(rotate + (45 * DEG2RAD)) * 50,
        pos.y + cosf(rotate + (45 * DEG2RAD)) * 50
    };

    // Проверяем, есть ли препятствие на пути автомобиля среди простых автомобилей
    for (int i = 0; i < simple_cars.size(); i++)
    {
        Vector2 position = simple_cars[i].get_pos();
        Vector2 dir = simple_cars[i].get_dir();

        // Если направления движения не совпадают по горизонтали, то проверяем треугольник
        if (direction.y == 0)
        {
            // Уступаем автомобилям на главной дороге
            if (CheckCollisionPointTriangle(position, pos, right_side, left_side)
                && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
            {
                saw_obstacle = true;
            }
        }

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light))
        {
            saw_obstacle = true;
        }
    }
    
    // Проверяем, есть ли препятствие на пути автомобиля среди специальных автомобилей
    for (int i = 0; i < spec_cars.size(); i++)
    {
        Vector2 position = spec_cars[i].get_pos();
        Vector2 dir = spec_cars[i].get_dir();
        // Уступаем Спец транспорту и проверяем наличие машин спереди, чтобы не было столкновения
        if ((CheckCollisionPointTriangle(position, pos, right_side, left_side)
            && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
            || CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light))
        {
            saw_obstacle = true;
        }
    }

    // Если препятствий нет, то меняем позицию автомобиля
    if (!saw_obstacle) Run(); 
}

// Метод для движения специальной машины
void Special_Car::Drive()
{
    // Получаем экземпляр класса Road_Controller и векторы специальных и простых автомобилей
    Road_Controller controller = Road_Controller::getInstance();
    std::vector<Special_Car> spec_cars = controller.get_spec_cars();
    std::vector<Simple_Car> simple_cars = controller.get_simple_cars(); 

    // Флаг, который показывает, была ли обнаружена препятствие на пути автомобиля
    bool saw_obstacle = false;

    // Вычисляем угол поворота автомобиля
    float rotate = atan2f(direction.x, direction.y);

    // Определяем координаты вершин треугольника специального автомобиля
    Vector2 right_side_light = {
        pos.x + sinf(rotate - (45 * DEG2RAD)) * 50,
        pos.y + cosf(rotate - (45 * DEG2RAD)) * 50
    };
    Vector2 left_side_light = {
        pos.x + sinf(rotate + (45 * DEG2RAD)) * 50,
        pos.y + cosf(rotate + (45 * DEG2RAD)) * 50
    };

    // Проходим по списку специальных автомобилей и проверяем наличие препятствия
    for (int i = 0; i < spec_cars.size(); i++)
    {
        Vector2 position = spec_cars[i].get_pos();
        Vector2 dir = spec_cars[i].get_dir();

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light))
        {
            saw_obstacle = true;
        }
    }

    // Проходим по списку простых автомобилей и проверяем наличие препятствия
    for (int i = 0; i < simple_cars.size(); i++)
    {
        Vector2 position = simple_cars[i].get_pos();
        Vector2 dir = simple_cars[i].get_dir();

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, pos, right_side_light, left_side_light))
        {
            saw_obstacle = true;
        }
    }

    // Если препятствий нет, то меняем
    if (!saw_obstacle) Run(); 
}