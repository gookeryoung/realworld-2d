#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globaldefs.h"

#include <SDL2/SDL.h>

GK_BEGIN_HEADER

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK16 0x0000f000
#define GMASK16	0x00000f00
#define BMASK16	0x000000f0
#define AMASK16	0x0000000f

#define RMASK24	0x00fc0000
#define GMASK24	0x0003f000
#define BMASK24	0x00000fc0
#define AMASK24	0x0000003f

#define RMASK32	0xff000000
#define GMASK32	0x00ff0000
#define BMASK32	0x0000ff00
#define AMASK32	0x000000ff
#else
#define RMASK16	0x0000000f
#define GMASK16	0x000000f0
#define BMASK16	0x00000f00
#define AMASK16	0x0000f000

#define RMASK24	0x0000003f
#define GMASK24	0x00000fc0
#define BMASK24	0x0003f000
#define AMASK24	0x00fc0000

#define RMASK32	0x000000ff
#define GMASK32	0x0000ff00
#define BMASK32	0x00ff0000
#define AMASK32	0xff000000
#endif // SDL_BYTEORDER == SDL_BIG_ENDIAN

/* You should always use this before operating on pixel level on a surface.
 * On most platforms your code will work without locking surfaces, but there
 * are platforms where you will experience crashes. */
#define GK_LOCKSURFACE(surface) do {\
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);\
    } while (0)

/* Unlock a surface, must be called after processing a locked surface. */
#define GK_UNLOCKSURFACE(surface) do {\
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);\
    } while (0)

/* Swap byte-order on big endian, otherwise do nothing.
 * Use this for example if you write 16 or 32 bit numbers into a binary
 * file to ensure it reads the same value on little and big endian. */
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define GK_BYTE_SWAP16(val)    (val)
#define GK_BYTE_SWAP32(val)    (val)
#else
#define GK_BYTE_SWAP16(val)    SDL_Swap16(val)
#define GK_BYTE_SWAP32(val)    SDL_Swap32(val)
#endif

#define color SDL_Color

GK_END_HEADER

#endif // GRAPHICS_H
