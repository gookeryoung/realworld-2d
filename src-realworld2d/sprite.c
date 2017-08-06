#include <SDL/SDL.h>
#include "animation.h"
#include "surface.h"
#include "sprite.h"

GKSprite *GKSprite_New(const char *fn, guint16 columns, guint16 rows, guint32 frames, guint8 type)
{
    GKSprite *ret = NULL;
    GK_NEW(ret, GKSprite);
    ret->_surface = GKSurface_NewFromFile(fn, GKTRUE);

    ret->_w = ret->_surface->_data->w / columns;
    ret->_h = ret->_surface->_data->h / rows;
    ret->_columns = columns;
    ret->_rows = rows;

    ret->_alpha = 0;

    ret->_animation = animation_new(type);
    ret->_animation->max_frames = frames;

    return (ret);
}

GKSprite *GKSprite_NewFromConfig(const char *config_str)
{
    guint32 columns, rows;
    guint32 frames;
    guint32 type;
    char file_path[GK_MAX_FILENAME_LEN];

    sscanf(config_str, "%d,%d,%d,%d:%s\n", &columns, &rows, &frames, &type, file_path);
    return (GKSprite_New(file_path, columns, rows, frames, type));
}

void GKSprite_Delete(GKSprite *s)
{
    animation_del(s->_animation);
    GKSurface_Delete(s->_surface);
    GK_DELETE(s);
}

void GKSprite_Blit(GKSprite *sp, GKSurface *s)
{
    int row = sp->_animation->cur_frame / sp->_columns;
    int col = sp->_animation->cur_frame % sp->_columns;

    assert(sp);
    assert(s);

    if (sp->_animation->is_active) {
        GKSurface_BlitRect(sp->_surface, s, sp->_w * col, sp->_h * row, sp->_w, sp->_h);
    }
    animation_on_animate(sp->_animation);
}

void GKSprite_SetPosition(GKSprite *s, gint16 x, gint16 y)
{
    GKSurface_SetPosition(s->_surface, x, y);
}

void GKSprite_SetFrameRate(GKSprite *s, guint16 frame_rate)
{
    s->_animation->frame_rate = frame_rate;
}

void GKSprite_SetColorkey(GKSprite *s, guint8 r, guint8 g, guint8 b)
{
    GKSurface_SetColorkey(s->_surface, r, g, b);
}
