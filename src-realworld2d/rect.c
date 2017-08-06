#include "rect.h"

rect
rect_intersect(rect r1, rect r2) {
    int x1 = GK_MAX(r1.x, r2.x);
    int y1 = GK_MAX(r1.y, r2.y);
    int x2 = GK_MIN(r1.x + r1.w, r2.x + r2.w);
    int y2 = GK_MIN(r1.y + r1.h, r2.y + r2.h);

    int width = x2 - x1;
    int height = y2 - y1;

    if(width > 0 && height > 0) {
        rect intersect = {x1, y1, width, height};
        return intersect;
    } else {
        rect intersect = {0, 0, 0, 0};
        return intersect;
    }
}

gbool
rect_collide(rect r1, rect r2) {
    int x1 = GK_MAX(r1.x, r2.x);
    int y1 = GK_MAX(r1.y, r2.y);
    int x2 = GK_MIN(r1.x + r1.w, r2.x + r2.w);
    int y2 = GK_MIN(r1.y + r1.h, r2.y + r2.h);

    return (gbool)(x2 - x1 > 0 && y2 - y1 > 0);
}

rect
rect_map(rect r, rect inside) {
    rect mapped;
    mapped.x = GK_MAX(r.x, inside.x) - GK_MIN(r.x, inside.x);
    mapped.y = GK_MAX(r.y, inside.y) - GK_MIN(r.y, inside.y);
    mapped.w = inside.w;
    mapped.h = inside.h;

    return (mapped);
}
