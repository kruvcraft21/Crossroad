#include "raylib.h"

class Traffic_sign
{
private:
    Texture2D image;
    Vector2 position;
public:
    Traffic_sign(const char* filepath, Vector2 pos);
    void Draw();
};