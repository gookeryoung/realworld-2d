#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include "globaldefs.h"

GK_BEGIN_HEADER

struct SDL_Surface *graphics_loadsurface(const char *file_name, int use_alpha);

GK_END_HEADER

#endif // GRAPHICSUTILS_H
