#ifndef GAMEMAPGROUND_H
#define GAMEMAPGROUND_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct GKGroundBlock {
    gint16 _worldX;
    gint16 _worldY;
    struct GKSurface *_surface;
} GKGroundBlock;

GKGroundBlock *GKGroundBlock_NewFromFile(const char *fn);
void GKGroundBlock_Delete(GKGroundBlock *gb);

typedef struct GKGround {
    guint16 _w;
    guint16 _h;
    int _columns;
    int _rows;

    guint16 _gridWidth;
    guint16 _gridHeight;

    struct GKGroundBlock **_blocks;
} GKGround;

GKGround *GKGround_NewFromFile(const char *fn);
void GKGround_Delete(GKGround *g);
void GKGround_Blit(GKGround *g, struct GKSurface *s);

GK_END_HEADER

#endif // GAMEMAPGROUND_H
