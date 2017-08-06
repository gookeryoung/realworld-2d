#include <SDL/SDL.h>
#include "animation.h"
#include "surface.h"
#include "sprite.h"

sprite *
sprite_new(const char *fn, guint16 columns, guint16 rows, guint32 frames, guint8 type) {
    sprite *ret = NULL;
    GK_NEW(ret, sprite);
    ret->surface = surface_new_fromfile(fn, GKTRUE);

    ret->w = ret->surface->data->w / columns;
    ret->h = ret->surface->data->h / rows;
    ret->columns = columns;
    ret->rows = rows;

    ret->alpha = 0;

    ret->animation = animation_new(type);
    ret->animation->max_frames = frames;

    return (ret);
}

sprite *
sprite_new_fromfile(const char *file_name) {
    guint32 columns, rows;
    guint32 frames;
    guint32 type;
    char file_path[GK_MAX_FILENAME_LEN];

    sscanf(file_name, "%d,%d,%d,%d:%s\n", &columns, &rows, &frames, &type, file_path);
    return (sprite_new(file_path, columns, rows, frames, type));
}

void
sprite_del(sprite *s) {
    animation_del(s->animation);
    surface_del(s->surface);
    GK_DELETE(s);
}

void
sprite_blit(sprite *sp, struct surface_ *s) {
    int row = sp->animation->cur_frame / sp->columns;
    int col = sp->animation->cur_frame % sp->columns;

    GK_ASSERT(sp);
    GK_ASSERT(s);

    if (sp->animation->is_active) {
        surface_blitrect(sp->surface, s, sp->w * col, sp->h * row, sp->w, sp->h);
    }
    animation_on_animate(sp->animation);
}

void
sprite_setposition(sprite *s, gint16 x, gint16 y){
    surface_setposition(s->surface, x, y);
}

void
sprite_setframerate(sprite *s, guint16 frame_rate) {
    s->animation->frame_rate = frame_rate;
}

void
sprite_setcolorkey(sprite *s, guint8 r, guint8 g, guint8 b) {
    surface_setcolorkey(s->surface, r, g, b);
}
