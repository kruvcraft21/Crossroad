#include "roadcontroller.h"

// Конструктор класса Road_Controller - создает дороги с различными параметрами и знаки дорожного движения
Road_Controller::Road_Controller() {
    // Создаем дорогу слева от центра
    Rectangle left_rect = {0, 200, 200, 100};
    Vector2 left_pos = {25, 275};
    // Создаем разметку
    Vector2 left_b = {0, 250},  left_e = {200, 250};
    Mark left_mark = {left_b, left_e};
    // Устанавливаем направление движения по дороге
    Vector2 left_dir = {1, 0};
    Road left(left_rect, left_pos, left_dir, left_mark);
    // Добавляем дорогу в коллекцию под именем "left"
    road_collection.insert({"left", left});

    // Создаем дорогу сверху от центра
    Rectangle up_rect = {200, 0, 100, 200};
    Vector2 up_pos = {225, 25};
    Vector2 up_b = {250, 0},    up_e = {250, 200};
    Mark up_mark = {up_b, up_e};
    Vector2 up_dir = {0, 1};
    Road up(up_rect, up_pos, up_dir, up_mark);
    road_collection.insert({"up", up});

    // Создаем дорогу снизу от центра
    Rectangle botton_rect = {200, 300, 100, 200};
    Vector2 botton_pos = {275, 475};
    Vector2 botton_b = {250, 300},  botton_e = {250, 500};
    Mark botton_mark = {botton_b, botton_e};
    Vector2 botton_dir = {0, -1};
    Road botton(botton_rect, botton_pos, botton_dir, botton_mark);
    road_collection.insert({"button", botton});

    // Создаем дорогу справа от центра
    Rectangle right_rect = {300, 200, 200, 100};
    Vector2 right_pos = {475, 225};
    Vector2 right_b = {300, 250},   right_e = {500, 250};
    Mark right_mark = {right_b, right_e};
    Vector2 right_dir = {-1, 0};
    Road right(right_rect, right_pos, right_dir, right_mark);
    road_collection.insert({"right", right});

    // Создаем центральную дорогу
    Rectangle center_rect = {200, 200, 100, 100};
    Vector2 center_pos = {0, 0};
    Road center(center_rect, center_pos);
    road_collection.insert({"center", center});

    // Создаем знаки дорожного движения
    traffic_signs.push_back(Traffic_sign("resources/glavnaya.png", {150, 150}));
    traffic_signs.push_back(Traffic_sign("resources/glavnaya.png", {300, 300}));
    traffic_signs.push_back(Traffic_sign("resources/neglavnaya3.png", {150, 300}));
    traffic_signs.push_back(Traffic_sign("resources/neglavnaya2.png", {300, 150}));
}

// Метод Start запускает окно
void Road_Controller::Start() {
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            // Отрисовываем все дороги
            for (auto &road : road_collection)
            {
                road.second.Draw();
            } 

            // Отрисовываем все знаки дорожного движения
            for (auto &traffic_sign : traffic_signs)
            {
                traffic_sign.Draw();
            }

            // Добавляем новые машины на дорогу
            AddCars();

            // Движение и отрисовка всех простых машин на дороге
            for (auto car = simple_cars.begin(); car != simple_cars.cend();)
            {
                car->Draw();
                car->Drive();
                // Удаляем машину если она вышла за границы экрана
                car = CheckCar(car->get_pos()) ? simple_cars.erase(car) : car + 1;
            }

            // Движение и отрисовка всех специальных машин на дороге
            for (auto car = spec_cars.begin(); car != spec_cars.end();
                 // Удаляем машину если она вышла за границы экрана
                 car = CheckCar(car->get_pos()) ? spec_cars.erase(car) : car + 1)
            {
                car->Draw();
                car->Drive();
            }

        EndDrawing();
    }
}
// Функция проверки нахождения машины за границами экрана
bool Road_Controller::CheckCar(Vector2 &pos) {
    bool a = pos.x > 500 || pos.x < 0;
    bool b = pos.y > 500 || pos.y < 0;
    return a || b;
}

// Метод для добавления машин на дорогу при нажатии мыши
void Road_Controller::AddCars()
{
    // Если нажата левая кнопка мыши
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousepos = GetMousePosition();
        // Проходим по каждой дороге в коллекции
        for (auto& [road_name, road] : road_collection)
        {
            // Если мышь находится на дороге, кроме центральной, создаем новую простую машину и добавляем ее на дорогу
            if (road_name != "center" && road.CheckCollisionPosition(mousepos)) {
                Simple_Car car(road.get_direction(), road.get_start_pos_car());
                AddSimpleCar(car);
            }

        }
    }
    // Если нажата правая кнопка мыши
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) 
    {
        Vector2 mousepos = GetMousePosition();
        // Проходим по каждой дороге в коллекции
        for (auto& [road_name, road] : road_collection)
        {
            // Если мышь находится на дороге, кроме центральной, создаем новую специальную машину и добавляем ее на дорогу
            if (road_name != "center" && road.CheckCollisionPosition(mousepos)) {
                Special_Car car(road.get_direction(), road.get_start_pos_car());
                AddSpecCar(car);
            }

        }
    }
}

// Метод для добавления новой простой машины
void Road_Controller::AddSimpleCar(Simple_Car &car) {
    // Если количество простых машин еще не достигло максимума, добавляем новую машину
    if (simple_cars.size() < MAX_CAR) {
        simple_cars.push_back(car);
    }
}

// Метод для добавления новой специальной машины
void Road_Controller::AddSpecCar(Special_Car &car)
{
    // Если количество специальных машин еще не достигло максимума, добавляем новую машину
    if (spec_cars.size() < MAX_SPEC_CAR)
    {
        spec_cars.push_back(car);
    }
}