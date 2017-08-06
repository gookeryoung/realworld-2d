#include <SDL/SDL.h>
#include "timer.h"
#include "graphicssystem.h"

static GKGraphicsSystem *__gkgraphics_system_instance__ = NULL;
static guint32 __gkgraphics_system_default_fps__ = 60;

GKGraphicsSystem *GKGraphicsSystem_Get(void)
{
    if (__gkgraphics_system_instance__ == NULL) {
        GK_NEW(__gkgraphics_system_instance__, GKGraphicsSystem);

        __gkgraphics_system_instance__->_timer = timer_new();
        __gkgraphics_system_instance__->_fps = __gkgraphics_system_default_fps__;

        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
            GK_BAILOUT("%s\n", "Failed to initialize graphics system.\n");
        }
    }

    return (__gkgraphics_system_instance__);
}

void GKGraphicsSystem_Free()
{
    if (__gkgraphics_system_instance__ != NULL) {
        timer_del(__gkgraphics_system_instance__->_timer);
        GK_DELETE(__gkgraphics_system_instance__);

        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
}

void GKGraphicsSystem_Delay(void)
{
    GKGraphicsSystem *s = GKGraphicsSystem_Get();

    if (timer_getticks(s->_timer) < 1000.0f / s->_fps) {
        SDL_Delay((guint32)(1000.0f / s->_fps - timer_getticks(s->_timer)));
    }
    timer_reset(s->_timer);
}

