#ifndef SURFACE_H
#define SURFACE_H

#include "globaldefs.h"
#include "rect.h"

GK_BEGIN_HEADER

typedef struct pixel_ {
    guint8 r;
    guint8 g;
    guint8 b;
    guint8 a;
} pixel;

pixel *pixel_new(guint8 r, guint8 g, guint8 b, guint8 a);
void pixel_del(pixel *p);

typedef struct surface_ {
    gbool use_alpha;             /* Use alpha will be slower.*/

    gint16 cx;
    gint16 cy;

    struct SDL_Surface *data;
} surface;

/* Methods for creating, copying or destorying a GKSurface object. */
surface *surface_new(void);
surface *surface_new_fromfile(const char *file_name, gbool use_alpha);
surface *surface_new_empty(guint16 w, guint16 h, guint8 depth, guint32 flag);
surface *surface_copy(surface *src);
void surface_del(surface *s);

/* Methods for drawing a GKSurface on to another. */
void surface_blit(surface *src, surface *dst);
void surface_blitxy(surface *src, surface *dst, gint16 ox, gint16 oy);
void surface_blitrect(surface *src, surface *dst, gint16 x, gint16 y, guint16 w, guint16 h);

/* Methods for collide checking. */
gbool surface_checkpixel(surface *s, gint16 x, gint16 y);
gbool surface_collidebox(surface *s1, surface *s2);
gbool surface_collide(surface *s1, surface *s2);

void surface_usealpha(surface *s);
void surface_ignorealpha(surface *s);

guint32 surface_map_rgba(surface *s, guint8 r, guint8 g, guint8 b, guint8 a);
guint8 surface_getdefaultdepth(void);
void surface_setdefaultdepth(guint8 depth);

/* Low level graphics functions. */
void surface_drawpixel(surface *s, gint16 x, gint16 y, guint32 color);
void surface_fillrect(surface *s, rect *r, guint32 color);

void surface_setposition(surface *s, gint16 x, gint16 y);
void surface_set(surface *s, guint16 w, guint16 h, guint8 depth, guint32 flag);
void surface_setalpha(surface *s, guint8 alpha);
void surface_setcolorkey(surface *s, guint8 r, guint8 g, guint8 b);
void surface_setcliprect(surface *s, gint16 x, gint16 y, guint16 w, guint16 h);

void surface_fill(surface *s, guint32 color);
void surface_loadpalette(surface *s);

/* Methods for accessing to GKSurface data. */
pixel *surface_getpixel(surface *s, gint16 x, gint16 y);
gint32 surface_getwidth(surface *s);
gint32 surface_getheight(surface *s);
rect surface_getbounds(surface *s);
guint32 surface_getcolorkey(surface *s);

#define surface_w(s) ((s)->data->w)
#define surface_h(s) ((s)->data->h)
#define surface_xy2index(s, x, y) (((s)->data->w) * y + x)

GK_END_HEADER

#endif // SURFACE_H
