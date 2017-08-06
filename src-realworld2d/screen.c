#include <SDL/SDL.h>
#include "graphics.h"
#include "screen.h"

static screen *_instance = NULL;

screen *
_screen_new(void) {
    screen *ret = NULL;
    GK_NEW(ret, screen);

    ret->data = surface_new();
    return (ret);
}

screen *
screen_get(void) {
    if (_instance == NULL) {
        _instance = _screen_new();
    }

    return (_instance);
}

void screen_del(void)
{
    if (_instance) {
        surface_del(_instance->data);
        GK_DELETE(_instance);
    }
}

surface *
screen_getsurface(void) {
    return (screen_get()->data);
}

void screen_setvideomode(gint32 w, gint32 h, gbool full_screen)
{
    guint32 flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL;
    screen *screen = screen_get();

    if (full_screen || (screen->data->data && (screen->data->data->flags & SDL_FULLSCREEN)))
        flags |= SDL_FULLSCREEN;

    screen->data->data = SDL_SetVideoMode(w, h, 0, flags);
    if (screen->data->data == NULL) {
        screen->data->data = SDL_SetVideoMode(640, 480, 0, flags);
        GK_WARNING("%s\n", SDL_GetError());
    }
}

int
screen_flip(void) {
    return (SDL_Flip(screen_get()->data->data));
}

void
screen_togglefullscreen(void) {
    screen *screen = screen_get();
    SDL_WM_ToggleFullScreen(screen->data->data);
}

void
screen_setcaption(const char *caption) {
    SDL_WM_SetCaption(caption, NULL);
}

void
screen_seticon(surface *surface) {
    SDL_WM_SetIcon(surface->data, NULL);
}

void
screen_showcursor(void) {
    SDL_ShowCursor(SDL_ENABLE);
}

void
screen_hidecursor(void) {
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

