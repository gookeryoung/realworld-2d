#ifndef RECT_H
#define RECT_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct point2d_ {
    gint32 x;
    gint32 y;
} point2d;

#define point_center2lt(pt,w,h) do{\
    (pt).x-=w/2;\
    (pt).y-=h/2;\
}while(0)

typedef struct size2d_ {
    guint32 w;
    guint32 h;
} size2d;

typedef struct rect_ {
    gint32 x;
    gint32 y;
    guint32 w;
    guint32 h;
} rect;

#define xy_in_rect(x,y,rx,ry,rw,rh) ((x)>=(rx)&&(x)<=(rx)+(rw)&&(y)>=(ry)&&(y)<=(ry)+(rh))

#define point_in_rect(p,r) xy_in_rect((p).x, (p).y, (r).x, (r).y, (r).w, (r).h)

rect rect_intersect(rect r1, rect r2);

gbool rect_collide(rect r1, rect r2);

rect rect_map(rect r, rect inside);

GK_END_HEADER

#endif // RECT_H
