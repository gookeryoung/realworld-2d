#include <stdio.h>
#include "stringutils.h"
#include "surface.h"
#include "gamemapground.h"

void
groundblock_del(ground_block *gb) {
    surface_del(gb->data);
    GK_DELETE(gb);
}

ground_block *
groundblock_new_fromfile(const char *fn) {
    ground_block *ret = NULL;
    GK_NEW(ret, ground_block);

    ret->data = surface_new_fromfile(fn, GKFALSE);
    ret->world_x = 0;
    ret->world_y = 0;

    return (ret);
}

void
ground_del(ground *g) {
    guint16 i;
    for (i = 0; i < g->columns * g->rows; ++i) {
        groundblock_del(g->data[i]);
    }
    GK_DELETE(g);
}

ground *
ground_new_fromfile(const char *fn) {
    guint16 i = 0, j = 0;
    FILE *f = NULL;
    char groundblock_path[GK_MAX_FILENAME_LEN];
    char groundblock_fn[GK_MAX_FILENAME_LEN];
    char groundblock_temppath[GK_MAX_FILENAME_LEN];

    ground *ret = NULL;
    GK_NEW(ret, ground);

    f = fopen(fn, "r");
    if (f == NULL) {
        GK_BAILOUT("Failed opening file %s", fn);
    }
    if (0 == fscanf(f, "%d, %d\n", &ret->rows, &ret->columns)) {
        GK_BAILOUT("failed to read data from %s\n", fn);
    }

    GK_MALLOC(ret->data, ground_block*, ret->columns * ret->rows);

    memset(groundblock_path, 0, GK_MAX_FILENAME_LEN);
    strncpy(groundblock_path, fn, string_rfindfirst(fn, '/') + 1);

    memset(groundblock_fn, 0, GK_MAX_FILENAME_LEN);
    memset(groundblock_temppath, 0, GK_MAX_FILENAME_LEN);

    for (i = 0; i < ret->columns * ret->rows; ++i) {
        strcpy(groundblock_temppath, groundblock_path);
        fscanf(f, "%s\n", groundblock_fn);
        strcat(groundblock_temppath, groundblock_fn);
        ret->data[i] = groundblock_new_fromfile(groundblock_temppath);
    }

    ret->grid_width = surface_getwidth(ret->data[0]->data);
    ret->grid_height = surface_getheight(ret->data[0]->data);
    ret->w = ret->grid_width * ret->columns;
    ret->h = ret->grid_height * ret->rows;

    for (j = 0; j < ret->rows; ++j) {
        for (i = 0; i < ret->columns; ++i) {
            ret->data[j * ret->columns + i]->world_x = (gint32)(ret->grid_width * (j + 0.5));
            ret->data[j * ret->columns + i]->world_y = (gint32)(ret->grid_height * (i + 0.5));
        }
    }

    return (ret);
}

void
ground_blit(ground *g, struct surface_ *s) {
    guint16 i;
    for (i = 0; i < g->columns * g->rows; ++i) {
        surface_blitxy(g->data[i]->data, s, g->data[i]->world_x, g->data[i]->world_y);
    }
}
