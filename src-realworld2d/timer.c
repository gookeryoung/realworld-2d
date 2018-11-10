#include <SDL/SDL.h>
#include "timer.h"

timer *
timer_new() {
    timer *ret = NULL;
    GK_NEW(ret, timer);

    ret->start_tick = 0;
    ret->pause_tick = 0;
    ret->is_started = GKFALSE;
    ret->is_paused = GKFALSE;

    return ret;
}

void
timer_del(timer *t) {
    GK_DELETE(t);
}

void
timer_start(timer *t) {
    if (!t->is_started) {
        t->is_started = GKTRUE;
        t->is_paused = GKFALSE;
        t->start_tick = SDL_GetTicks();
    } else {
        if (t->is_paused) {
            t->is_paused = GKFALSE;
            t->start_tick = SDL_GetTicks() - t->pause_tick;
            t->pause_tick = 0;
        }
    }
}

void
timer_reset(timer *t) {
    if (t->is_started) {
        t->start_tick = SDL_GetTicks();
    }
}

void
timer_pause(timer *t) {
    if (t->is_started && (!t->is_paused)) {
        t->is_paused = GKTRUE;
        t->is_started = GKFALSE;
        t->pause_tick = SDL_GetTicks() - t->start_tick;
    }
}

void
timer_stop(timer *t) {
    t->is_started = GKFALSE;
    t->is_paused = GKFALSE;
}

gint32
timer_getticks(timer *t) {
    if (t->is_started) {
        if (t->is_paused) {
            return t->pause_tick;
        } else {
            return SDL_GetTicks() - t->start_tick;
        }
    }

    return 0;
}
