#pragma once

#include "raylib.h"

typedef struct Mark {
    Vector2 begin_pos;
    Vector2 end_pos;
} Mark;

class Road {
private:
    Mark mark;
    bool isMarking;

public:
    Vector2 direction = {0, 0};
    Vector2 start;
    Rectangle skelet;

public:
    Road(Rectangle &rect,Vector2 &startpos);
    Road(Rectangle &rect,Vector2 &startpos, Vector2 &dir);
    Road(Rectangle &rect,Vector2 &startpos, Vector2 &dir, Mark& m);
    void Draw();
};