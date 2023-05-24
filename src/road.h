#pragma once

#include "raylib.h"

typedef struct Mark {
    Vector2 begin_pos;
    Vector2 end_pos;
} Mark;

class Road {
private:
    Rectangle skelet;
    Mark mark;
    bool isMarking;
    
public:
    Vector2 direction;
    Vector2 start;

public:
    Road(Rectangle &rect,Vector2 &startpos, Vector2 &dir);
    Road(Rectangle &rect,Vector2 &startpos, Vector2 &dir, Mark& m);
    void Draw();
};