#ifndef SURFACE_H
#define SURFACE_H

#include "globaldefs.h"
#include "rect.h"

GK_BEGIN_HEADER

typedef struct GKPixel {
    guint8 r;
    guint8 g;
    guint8 b;
    guint8 a;
} GKPixel;

GKPixel *GKPixel_New(guint8 r, guint8 g, guint8 b, guint8 a);
void GKPixel_Delete(GKPixel *p);

typedef struct GKSurface {
    gbool _useAlpha;             /* Use alpha will be slower.*/

    gint16 _cx;
    gint16 _cy;

    struct SDL_Surface *_data;
} GKSurface;

/* Methods for creating, copying or destorying a GKSurface object. */
GKSurface *GKSurface_New(void);
GKSurface *GKSurface_NewFromFile(const char *file_name, gbool use_alpha);
GKSurface *GKSurface_NewEmptySurface(guint16 w, guint16 h, guint8 depth, guint32 flag);
GKSurface *GKSurface_Duplicate(GKSurface *src);
void GKSurface_Delete(GKSurface *s);

/* Methods for drawing a GKSurface on to another. */
void GKSurface_Blit(GKSurface *src, GKSurface *dst);
void GKSurface_BlitXY(GKSurface *src, GKSurface *dst, gint16 ox, gint16 oy);
void GKSurface_BlitRect(GKSurface *src, GKSurface *dst, gint16 x, gint16 y, guint16 w, guint16 h);

/* Methods for collide checking. */
gbool GKSurface_CheckPixel(GKSurface *s, gint16 x, gint16 y);
gbool GKSurface_BoxCollide(GKSurface *s1, GKSurface *s2);
gbool GKSurface_Collide(GKSurface *s1, GKSurface *s2);

void GKSurface_UseAlpha(GKSurface *s);
void GKSurface_IgnoreAlpha(GKSurface *s);

guint32 GKSurface_MapRGBA(GKSurface *s, guint8 r, guint8 g, guint8 b, guint8 a);
int GKSurface_GetDefaultDepth(void);
void GKSurface_SetDefaultDepth(guint8 depth);

/* Low level graphics functions. */
void GKSurface_DrawPixel(GKSurface *s, gint16 x, gint16 y, guint32 color);
void GKSurface_FillRect(GKSurface *s, rect *r, guint32 color);

void GKSurface_SetPosition(GKSurface *s, gint16 x, gint16 y);
void GKSurface_Set(GKSurface *s, guint16 w, guint16 h, guint8 depth, guint32 flag);
void GKSurface_SetAlpha(GKSurface *s, guint8 alpha);
void GKSurface_SetColorkey(GKSurface *s, guint8 r, guint8 g, guint8 b);
void GKSurface_SetClipRect(GKSurface *s, gint16 x, gint16 y, guint16 w, guint16 h);

void GKSurface_Fill(GKSurface *s, guint32 color);
void GKSurface_LoadPalette(GKSurface *s);

/* Methods for accessing to GKSurface data. */
GKPixel *GKSurface_GetPixel(GKSurface *s, gint16 x, gint16 y);
gint32 GKSurface_GetWidth(GKSurface *s);
gint32 GKSurface_GetHeight(GKSurface *s);
rect GKSurface_GetBounds(GKSurface *s);
guint32 GKSurface_GetColorkey(GKSurface *s);

#define GKSurface_W(s) ((s)->_data->w)
#define GKSurface_H(s) ((s)->_data->h)
#define GKSurface_XY2Index(s, x, y) (((s)->_data->w) * y + x)

GK_END_HEADER

#endif // SURFACE_H
