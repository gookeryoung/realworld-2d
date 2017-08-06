#ifndef PALETTE_H
#define PALETTE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

#define PALETTE_SIZE 768

typedef struct palette_ {

    guint32 pal[PALETTE_SIZE];
    struct SDL_Palette *data;
} palette;

palette *palette_get(void);
void palette_del(void);
guint32 palette_getcolor(guint16 index);


GK_END_HEADER

#endif // PALETTE_H
