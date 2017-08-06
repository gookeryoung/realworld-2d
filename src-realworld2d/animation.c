#include <SDL/SDL.h>
#include "animation.h"

typedef struct func_map_{
    animation_type type;
    void (*animate_func)(animation *a);
} func_map;

static void _animate_loop(animation *a);
static void _animate_singleshot(animation *a);
static void _animate_singleback(animation *a);
static void _animate_singlestay(animation *a);
static void _animate_oscillate(animation *a);

static const func_map funcmap_animate[] = {
    {GKANIMATION_TYPE_LOOP, _animate_loop},
    {GKANIMATION_TYPE_SINGLE_SHOT, _animate_singleshot},
    {GKANIMATION_TYPE_SINGLE_BACK, _animate_singleback},
    {GKANIMATION_TYPE_SINGLE_STAY, _animate_singlestay},
    {GKANIMATION_TYPE_OSCILLATE, _animate_oscillate}
};

animation *
animation_new(animation_type type) {
    animation *ret = NULL;
    GK_NEW(ret, animation);

    GK_REQUIRE(type >= GKANIMATION_TYPE_LOOP && type <= GKANIMATION_TYPE_OSCILLATE,
               "Invalid animation type");

    ret->cur_frame = 0;
    ret->frame_step = 1;
    ret->max_frames = 0;

    ret->frame_rate = 100;
    ret->old_time = 0L;
    ret->type = type;
    ret->is_active = GKTRUE;
    ret->is_animating = GKTRUE;

    GK_NEW(ret->vtbl, animation_interface);
    ret->vtbl->on_animate = funcmap_animate[type].animate_func;

    return (ret);
}

void
animation_del(animation *a) {
    GK_DELETE(a->vtbl);
    GK_DELETE(a);
}

void
animation_on_animate(animation *a) {
    funcmap_animate[a->type].animate_func(a);
}

void
animation_settype(animation *a, animation_type type) {
    a->type = type;
    a->vtbl->on_animate = funcmap_animate[type].animate_func;
}

void
animation_setcurrentframe(animation *a, int cur_frame) {
    a->cur_frame = cur_frame;
}

void animation_setanimating(animation *a, gbool animating)
{
    a->is_animating = animating;
}

void _animate_loop(animation *a)
{
    if (a->old_time + a->frame_rate > SDL_GetTicks())
        return;

    a->old_time = SDL_GetTicks();
    a->cur_frame += a->frame_step;

    if (a->cur_frame >= a->max_frames) {
        a->cur_frame = 0;
    }
}

void _animate_singleshot(animation *a)
{
    if (a->old_time + a->frame_rate > SDL_GetTicks() || !a->is_animating)
        return;

    a->old_time = SDL_GetTicks();
    a->cur_frame += a->frame_step;

    if (a->cur_frame >= a->max_frames) {
        a->is_active = GKFALSE;
    }
}

void _animate_singleback(animation *a)
{
    if (a->old_time + a->frame_rate > SDL_GetTicks() || !a->is_animating)
        return;

    a->old_time = SDL_GetTicks();
    a->cur_frame += a->frame_step;

    if (a->cur_frame >= a->max_frames) {
        a->frame_step *= -1;
        a->is_animating = GKFALSE;
    }
}

void _animate_singlestay(animation *a)
{
    if (a->old_time + a->frame_rate > SDL_GetTicks() || !a->is_animating)
        return;

    a->old_time = SDL_GetTicks();
    a->cur_frame += a->frame_step;

    if (a->cur_frame >= a->max_frames) {
        a->cur_frame = a->max_frames - 1;
        a->is_animating = GKFALSE;
    }
}

void _animate_oscillate(animation *a)
{
    if (a->old_time + a->frame_rate > SDL_GetTicks() || !a->is_animating)
        return;

    a->old_time = SDL_GetTicks();
    a->cur_frame += a->frame_step;

    if (a->cur_frame >= a->max_frames) {
        a->frame_step *= -1;
        a->cur_frame += a->frame_step;
    } else if (a->cur_frame <= 0) {
        a->frame_step *= -1;
        a->cur_frame += a->frame_step;
    }
}
