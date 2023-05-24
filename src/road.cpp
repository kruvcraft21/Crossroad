#include "road.h"

Road::Road(Rectangle &rect, Vector2 &startpos) {
    skelet = rect;
    start = startpos;
}


Road::Road(Rectangle &rect, Vector2 &startpos, Rectangle &finalpos, Vector2 &dir) : Road(rect, startpos)
{
    direction = dir;
    final = finalpos;
}

Road::Road(Rectangle &rect, Vector2 &startpos, Rectangle &finalpos, Vector2 &dir, Mark &m) : Road(rect, startpos, finalpos, dir) {
    isMarking = true;
    mark = m;
}

void Road::Draw() {
    DrawRectangleRec(skelet, GRAY);
    if (isMarking) {
        DrawLineV(mark.begin_pos, mark.end_pos, WHITE);
    }
}