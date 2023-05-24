#include "road.h"

Road::Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir) {
    skelet = rect;
    start = startpos;
    direction = dir;
}

Road::Road(Rectangle &rect, Vector2 &startpos, Vector2 &dir, Mark &m) : Road(rect, startpos, dir) {
    isMarking = true;
    mark = m;
}

void Road::Draw() {
    DrawRectangleRec(skelet, GRAY);
    if (isMarking) {
        DrawLineV(mark.begin_pos, mark.end_pos, WHITE);
    }
}