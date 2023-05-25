#include "traffic_sign.h"

Traffic_sign::Traffic_sign(const char *filepath, Vector2 pos)
{
    image = LoadTexture(filepath);
    position = pos;
}

void Traffic_sign::Draw()
{
    DrawTextureV(image, position, WHITE);
}
