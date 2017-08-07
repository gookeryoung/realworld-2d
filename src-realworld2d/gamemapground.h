#ifndef GAMEMAPGROUND_H
#define GAMEMAPGROUND_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct ground_block_ {
    gint16 world_x;
    gint16 world_y;
    struct surface_ *data;
} ground_block;

ground_block *groundblock_new_fromfile(const char *fn);
void groundblock_del(ground_block *gb);

typedef struct ground_ {
    guint16 w;
    guint16 h;
    int columns;
    int rows;

    guint16 grid_width;
    guint16 grid_height;

    struct ground_block_ **data;
} ground;

ground *ground_new_fromfile(const char *fn);
void ground_del(ground *g);
void ground_blit(ground *g, struct surface_ *s);

GK_END_HEADER

#endif // GAMEMAPGROUND_H
