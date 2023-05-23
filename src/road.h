#pragma once

#include "raylib.h"

typedef struct Mark {
    Vector2 begin_pos;
    Vector2 end_pos;
} Mark;

class Road {
private:
    Rectangle skelet;
    Vector2 start;
    Mark mark;
    bool isMarking;

public:
    Road(Rectangle &rect,Vector2 &startpos);
    Road(Rectangle &rect,Vector2 &startpos, Mark& m);
    void Draw();
};