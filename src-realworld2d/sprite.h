#ifndef SPRITE_H
#define SPRITE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct sprite_
{
    guint16 w;
    guint16 h;

    guint16 columns;
    guint16 rows;

    guint8 alpha;

    struct animation_ *animation;
    struct surface_ *surface;
} sprite;

/* Methods for creating and deleting GKSprite objects. */
sprite *sprite_new(const char *fn, guint16 columns, guint16 rows, guint32 frames, guint8 type);
sprite *sprite_new_fromfile(const char *file_name);
void sprite_del(sprite *s);

/* Methods for blitting GKSprite. */
void sprite_blit(sprite *sp, struct surface_ *s);

/* Methods for misc operations. */
void sprite_setposition(sprite *s, gint16 x, gint16 y);
void sprite_setframerate(sprite *s, guint16 frame_rate);
void sprite_setcolorkey(sprite *s, guint8 r, guint8 g, guint8 b);

#define sprite_getwidth(s) ((s)->w)
#define sprite_getheight(s) ((s)->h)
#define sprite_getcolumns(s) ((s)->columns)
#define sprite_getrows(s) ((s)->rows)
#define sprite_getalpha(s) ((s)->alpha)
#define sprite_getanimation(s) ((s)->animation)
#define spriate_getsurface(s) ((s)->surface)
#define sprite_getcurrentframe(s) ((s)->_animation->cur_frame)

GK_END_HEADER

#endif // SPRITE_H
