#ifndef PALETTE_H
#define PALETTE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

#define GKPALETTE_SIZE 768

typedef struct GKPalette {

    guint32 _pal[GKPALETTE_SIZE];
    struct SDL_Palette *_palette;
} GKPalette;

GKPalette *GKPalette_GetInstance(void);
void GKPalette_DeleteInstance(void);
guint32 GKPalette_GetColor(guint16 index);


GK_END_HEADER

#endif // PALETTE_H
