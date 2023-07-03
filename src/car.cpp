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
Vector2& Car::get_pos() {
    return pos;
}

// Метод для движения машины, обновляет позицию автомобиля в соответствии с его направлением и скоростью
void Car::Run() {
    // Вычисляем разницу в координатах
    auto delta_x = direction.x * speed;
    auto delta_y = direction.y * speed;

    // Получаем новую позицию машины
    pos.x += delta_x;
    pos.y += delta_y;

    // Сдвигаем треугольники обзора на разницу
    for (auto &triangle : overview_car)
    {
        for (auto &point : triangle.second)
        {
            point.x += delta_x;
            point.y += delta_y;
        }
    }
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

    // Вычисляем угол поворота автомобиля
    float rotate = atan2f(direction.x, direction.y);

    // Вычисляем треугольник обзора для центра перекрёстка
    std::array<Vector2, 3> center_triangle = {
        startpos,
        {
            startpos.x + sinf(rotate - (DEGTORAD50)) * 110,
            startpos.y + cosf(rotate - (DEGTORAD50)) * 110
        },
        {
            startpos.x + sinf(rotate + (DEGTORAD50)) * 110,
            startpos.y + cosf(rotate + (DEGTORAD50)) * 110
        }
    };

    // Вычисляем треугольник обзора для проверки перед машиной
    std::array<Vector2, 3> front_triangle = {
        startpos,
        {
            startpos.x + sinf(rotate - (DEGTORAD45)) * 50,
            startpos.y + cosf(rotate - (DEGTORAD45)) * 50
        },
        {
            startpos.x + sinf(rotate + (DEGTORAD45)) * 50,
            startpos.y + cosf(rotate + (DEGTORAD45)) * 50
        }
    };

    // Добавляем треугольники в контейнер
    overview_car.insert({"center_triangle", center_triangle});
    overview_car.insert({"front_triangle", front_triangle});
}

// Метод для движения простой машины
void Simple_Car::Drive()
{
    // Получаем экземпляр класса Road_Controller и векторы специальных и простых автомобилей
    auto controller = Road_Controller::getInstance();
    std::vector<Special_Car>& spec_cars = controller.get_spec_cars();
    std::vector<Simple_Car>& simple_cars = controller.get_simple_cars(); 

    // Флаг, который показывает, было ли обнаружена препятствие на пути автомобиля
    bool saw_obstacle = false;

    // Получаем треугольники обзора
    auto center_triangle = overview_car["center_triangle"];
    auto front_triangle = overview_car["front_triangle"];

    // Проверяем, есть ли препятствие на пути автомобиля среди простых автомобилей
    for (auto &car : simple_cars)
    {
        Vector2 position = car.get_pos();
        Vector2 dir = car.get_dir();

        // Если направления движения не совпадают по горизонтали, то проверяем треугольник
        if (direction.y == 0)
        {
            // Уступаем автомобилям на главной дороге
            if (CheckCollisionPointTriangle(position, center_triangle[0], center_triangle[1], center_triangle[2])
                && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
            {
                saw_obstacle = true;
            }
        }

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, front_triangle[0], front_triangle[1], front_triangle[2]))
        {
            saw_obstacle = true;
        }
    }
    
    // Проверяем, есть ли препятствие на пути автомобиля среди специальных автомобилей
    for (auto &car : spec_cars)
    {
        Vector2 position = car.get_pos();
        Vector2 dir = car.get_dir();
        // Уступаем Спец транспорту и проверяем наличие машин спереди, чтобы не было столкновения
        if ((CheckCollisionPointTriangle(position, center_triangle[0], center_triangle[1], center_triangle[2])
            && (abs(direction.x) != abs(dir.x)) && (abs(direction.y) != dir.y))
            || CheckCollisionPointTriangle(position, front_triangle[0], front_triangle[1], front_triangle[2]))
        {
            saw_obstacle = true;
        }
    }

    // Если препятствий нет, то меняем позицию автомобиля
    if (!saw_obstacle) Run(); 
}

Special_Car::Special_Car(Vector2& dir, Vector2& startpos) : Car(dir, startpos)
{
    // Вычисляем угол поворота автомобиля
    float rotate = atan2f(direction.x, direction.y);

    // Вычисляем треугольник обзора для проверки перед машиной
    std::array<Vector2, 3> front_triangle = {
        startpos,
        {
            startpos.x + sinf(rotate - (DEGTORAD45)) * 50,
            startpos.y + cosf(rotate - (DEGTORAD45)) * 50
        },
        {
            startpos.x + sinf(rotate + (DEGTORAD45)) * 50,
            startpos.y + cosf(rotate + (DEGTORAD45)) * 50
        }
    };

    // Добавляем треугольник в контейнер
    overview_car.insert(make_pair("front_triangle", front_triangle));
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

    // Получаем треугольник обзора
    auto front_triangle = overview_car["front_triangle"];

    // Проходим по списку специальных автомобилей и проверяем наличие препятствия
    for (auto &car : spec_cars)
    {
        Vector2 position = car.get_pos();

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, front_triangle[0], front_triangle[1], front_triangle[2]))
        {
            saw_obstacle = true;
        }
    }

    // Проходим по списку простых автомобилей и проверяем наличие препятствия
    for (auto &car : simple_cars)
    {
        Vector2 position = car.get_pos();

        // Проверяем наличие машин спереди, чтобы не было столкновения
        if (CheckCollisionPointTriangle(position, front_triangle[0], front_triangle[1], front_triangle[2]))
        {
            saw_obstacle = true;
        }
    }

    // Если препятствий нет, то меняем
    if (!saw_obstacle) Run(); 
}