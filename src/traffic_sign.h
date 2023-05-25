#include "raylib.h"

// Этот класс представляет объект-дорожный знак
class Traffic_sign
{
private:
    Texture2D image; // текстура знака
    Vector2 position; // позиция знака на карте
public:
    Traffic_sign(const char* filepath, Vector2 pos); // конструктор класса
    void Draw(); // функция рисования знака
};