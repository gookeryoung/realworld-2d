#include <SDL/SDL.h>
#include "timer.h"
#include "graphicssystem.h"

static graphics_system *_instance = NULL;
static guint32 _default_fps = 60;

graphics_system *
graphicssytem_get(void) {
    if (_instance == NULL) {
        GK_NEW(_instance, graphics_system);

        _instance->timer = timer_new();
        _instance->fps = _default_fps;

        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
            GK_BAILOUT("%s\n", "Failed to initialize graphics system.\n");
        }
    }

    return (_instance);
}

void
graphicssystem_del() {
    if (_instance != NULL) {
        timer_del(_instance->timer);
        GK_DELETE(_instance);

        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
}

void
graphicssystem_delay(void) {
    graphics_system *s = graphicssytem_get();

    if (timer_getticks(s->timer) < 1000.0f / s->fps) {
        SDL_Delay((guint32)(1000.0f / s->fps - timer_getticks(s->timer)));
    }
    timer_reset(s->timer);
}

