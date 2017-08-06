#ifndef SPRITE_H
#define SPRITE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct GKSprite
{
    guint16 _w;
    guint16 _h;

    guint16 _columns;
    guint16 _rows;

    guint8 _alpha;

    struct animation_ *_animation;
    struct GKSurface *_surface;
} GKSprite;

/* Methods for creating and deleting GKSprite objects. */
GKSprite *GKSprite_New(const char *fn, guint16 columns, guint16 rows, guint32 frames, guint8 type);
GKSprite *GKSprite_NewFromConfig(const char *config_str);
void GKSprite_Delete(GKSprite *s);

/* Methods for blitting GKSprite. */
void GKSprite_Blit(GKSprite *sp, struct GKSurface *s);

/* Methods for misc operations. */
void GKSprite_SetPosition(GKSprite *s, gint16 x, gint16 y);
void GKSprite_SetFrameRate(GKSprite *s, guint16 frame_rate);
void GKSprite_SetColorkey(GKSprite *s, guint8 r, guint8 g, guint8 b);

#define GKSprite_GetWidth(s) ((s)->_w)
#define GKSprite_GetHeight(s) ((s)->_h)
#define GKSprite_GetColumns(s) ((s)->_columns)
#define GKSprite_GetRows(s) ((s)->_rows)
#define GKSprite_GetAlpha(s) ((s)->_alpha)
#define GKSprite_GetAnimation(s) ((s)->_animation)
#define GKSprite_GetSurface(s) ((s)->_surface)
#define GKSprite_GetCurrentFrame(s) ((s)->_animation->_currentFrame)

GK_END_HEADER

#endif // SPRITE_H
