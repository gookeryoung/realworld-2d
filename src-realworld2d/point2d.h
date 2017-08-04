#ifndef POINT2D_H
#define POINT2D_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct point2d_ {
    gint32 x;
    gint32 y;
} point2d;

point2d *point2d_new(gint32 x, gint32 y);
void point2d_del(point2d *pt);

GK_END_HEADER

#endif // POINT2D_H
