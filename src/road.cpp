#include "road.h"

Road::Road(Rectangle &rect, Vector2 &startpos) {
    skelet = rect;
    start = startpos;
}

Road::Road(Rectangle &rect, Vector2 &startpos, Mark &m) : Road(rect, startpos) {
    isMarking = true;
    mark = m;
}

void Road::Draw() {
    DrawRectangleRec(skelet, GRAY);
    if (isMarking) {
        DrawLineV(mark.begin_pos, mark.end_pos, WHITE);
    }
}