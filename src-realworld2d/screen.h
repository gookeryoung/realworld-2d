#ifndef SCREEN_H
#define SCREEN_H

#include "globaldefs.h"
#include "surface.h"

GK_BEGIN_HEADER

typedef struct screen_ {
    struct surface_ *data;
} screen;

screen *screen_get(void);
void screen_del(void);
surface *screen_getsurface(void);
void screen_setvideomode(gint32 w, gint32 h, gbool full_screen);
int screen_flip(void);
void screen_togglefullscreen(void);
void screen_setcaption(const char *caption);
void screen_seticon(surface *surface);
void screen_showcursor(void);
void screen_hidecursor(void);

GK_STATIC_INLINE gint32 screen_getwidth() { return (surface_getwidth(screen_getsurface())); }
GK_STATIC_INLINE gint32 screen_getheight() { return (surface_getheight(screen_getsurface())); }

GK_END_HEADER

#endif // SCREEN_H
