#include <stdio.h>
#include "stringutils.h"
#include "surface.h"
#include "gamemapground.h"

void GKGroundBlock_Delete(GKGroundBlock *gb)
{
    GKSurface_Delete(gb->_surface);
    GK_DELETE(gb);
}

GKGroundBlock *GKGroundBlock_NewFromFile(const char *fn)
{
    GKGroundBlock *ret = NULL;
    GK_NEW(ret, GKGroundBlock);

    ret->_surface = GKSurface_NewFromFile(fn, GKFALSE);
    ret->_worldX = 0;
    ret->_worldY = 0;

    return (ret);
}

void GKGround_Delete(GKGround *g)
{
    guint16 i;
    for (i = 0; i < g->_columns * g->_rows; ++i) {
        GKGroundBlock_Delete(g->_blocks[i]);
    }
    GK_DELETE(g);
}

GKGround *GKGround_NewFromFile(const char *fn)
{
    guint16 i = 0, j = 0;
    FILE *f = NULL;
    char groundblock_path[GK_MAX_FILENAME_LEN];
    char groundblock_fn[GK_MAX_FILENAME_LEN];
    char groundblock_temppath[GK_MAX_FILENAME_LEN];

    GKGround *ret = NULL;
    GK_NEW(ret, GKGround);

    f = fopen(fn, "r");
    if (f == NULL) {
        GK_BAILOUT("Failed opening file %s", fn);
    }
    if (0 == fscanf(f, "%d, %d\n", &ret->_rows, &ret->_columns)) {
        GK_BAILOUT("failed to read data from %s\n", fn);
    }

    GK_MALLOC(ret->_blocks, GKGroundBlock*, ret->_columns * ret->_rows);

    memset(groundblock_path, 0, GK_MAX_FILENAME_LEN);
    strncpy(groundblock_path, fn, GKString_RFindFirst(fn, '/') + 1);

    memset(groundblock_fn, 0, GK_MAX_FILENAME_LEN);
    memset(groundblock_temppath, 0, GK_MAX_FILENAME_LEN);

    for (i = 0; i < ret->_columns * ret->_rows; ++i) {
        strcpy(groundblock_temppath, groundblock_path);
        fscanf(f, "%s\n", groundblock_fn);
        strcat(groundblock_temppath, groundblock_fn);
        ret->_blocks[i] = GKGroundBlock_NewFromFile(groundblock_temppath);
    }

    ret->_gridWidth = GKSurface_GetWidth(ret->_blocks[0]->_surface);
    ret->_gridHeight = GKSurface_GetHeight(ret->_blocks[0]->_surface);
    ret->_w = ret->_gridWidth * ret->_columns;
    ret->_h = ret->_gridHeight * ret->_rows;

    for (j = 0; j < ret->_rows; ++j) {
        for (i = 0; i < ret->_columns; ++i) {
            ret->_blocks[j * ret->_columns + i]->_worldX = (gint32)(ret->_gridWidth * (j + 0.5));
            ret->_blocks[j * ret->_columns + i]->_worldY = (gint32)(ret->_gridHeight * (i + 0.5));
        }
    }

    return (ret);
}

void GKGround_Blit(GKGround *g, struct GKSurface *s)
{
    guint16 i;
    for (i = 0; i < g->_columns * g->_rows; ++i) {
        GKSurface_BlitXY(g->_blocks[i]->_surface, s, g->_blocks[i]->_worldX, g->_blocks[i]->_worldY);
    }
}
