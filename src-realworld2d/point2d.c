#include "point2d.h"

point2d *
point2d_new(gint32 x, gint32 y) {
    point2d *ret = NULL;
    GK_NEW(ret, point2d);

    ret->x = x;
    ret->y = y;

    return ret;
}

void
point2d_del(point2d *pt){
    GK_DELETE(pt);
}

