#include <SDL/SDL.h>
#include "graphics.h"
#include "screen.h"

static GKScreen *__GKScreen_Instance__ = NULL;

struct GKScreen *__GKScreen_New(void)
{
    GKScreen *ret = NULL;
    GK_NEW(ret, GKScreen);

    ret->_surface = GKSurface_New();
    return (ret);
}

GKScreen *GKScreen_Get(void)
{
    if (__GKScreen_Instance__ == NULL) {
        __GKScreen_Instance__ = __GKScreen_New();
    }

    return (__GKScreen_Instance__);
}

GKSurface *GKScreen_GetSurface(void)
{
    return (GKScreen_Get()->_surface);
}

void GKScreen_Free(void)
{
    if (__GKScreen_Instance__) {
        GKSurface_Delete(__GKScreen_Instance__->_surface);
        GK_DELETE(__GKScreen_Instance__);
    }
}

void GKScreen_SetVideoMode(gint32 w, gint32 h, gbool full_screen)
{
    guint32 flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL;
    GKScreen *screen = GKScreen_Get();

    if (full_screen || (screen->_surface->_data && (screen->_surface->_data->flags & SDL_FULLSCREEN)))
        flags |= SDL_FULLSCREEN;

    screen->_surface->_data = SDL_SetVideoMode(w, h, 0, flags);
    if (screen->_surface->_data == NULL) {
        screen->_surface->_data = SDL_SetVideoMode(640, 480, 0, flags);
        GK_WARNING("%s\n", SDL_GetError());
    }
}

int GKScreen_Flip(void)
{
    return (SDL_Flip(GKScreen_Get()->_surface->_data));
}

void GKScreen_ToggleFullScreen(void)
{
    GKScreen *screen = GKScreen_Get();
    SDL_WM_ToggleFullScreen(screen->_surface->_data);
}

void GKScreen_SetCaption(const char *caption)
{
    SDL_WM_SetCaption(caption, NULL);
}

void GKScreen_SetIcon(GKSurface *surface)
{
    SDL_WM_SetIcon(surface->_data, NULL);
}

void GKScreen_ShowCursor(void)
{
    SDL_ShowCursor(SDL_ENABLE);
}

void GKScreen_HideCursor(void)
{
    SDL_ShowCursor(SDL_DISABLE);
}

//GKgbool GKScreen_Fade(U8 fade_to)
//{
//    GKScreen *screen = GKScreen_Get();
//    U8 alpha = screen->_surface->_data->format->alpha;

//    if (alpha == fade_to) {
//        return (GKFalse);
//    } else if (alpha < fade_to) {
//        return (GKScreen_Rise(fade_to));
//    }

//    GKSurface temp = *screen->_surface;
//    SDL_DisplayFormat(temp._data);
//    const guint32 black = GKSurface_MapRGBA(&temp, 0, 0, 0, 0);
//    GKSurface_Blit(screen->_surface, &temp);

//    while (alpha > fade_to) {
//        alpha -= (alpha - 10 > fade_to ? 10 : (alpha - fade_to));
//        GKSurface_Fill(screen->_surface, black);
//        GKSurface_SetAlpha(screen->_surface, alpha);
//        GKSurface_Blit(&temp, screen->_surface);
//        GKScreen_Flip();
//        SDL_Delay(10);
//    }

//    return (GKTrue);
//}

//GKgbool GKScreen_Rise(U8 rise_to)
//{
//}

