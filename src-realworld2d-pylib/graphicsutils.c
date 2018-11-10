#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphicsutils.h"

SDL_Surface *
graphics_loadsurface(const char *file_name, int use_alpha) {
    SDL_Surface *loaded = NULL;
    SDL_Surface *ret = NULL;

    loaded = IMG_Load(file_name);

    if (loaded != NULL) {
//        ret = SDL_DisplayFormatAlpha(loaded);
        ret = use_alpha ? SDL_DisplayFormatAlpha(loaded) : SDL_DisplayFormat(loaded);
        printf("ret at %p", ret);
        SDL_FreeSurface(loaded);
    } else {
        GK_BAILOUT("Failed loading surface [%s]: [%s]", file_name, IMG_GetError());
    }

    return (loaded);
}
