#ifndef ANIMATION_H
#define ANIMATION_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct animation_ animation;

typedef enum animation_type_ {
    GKANIMATION_TYPE_LOOP = 0,
    GKANIMATION_TYPE_SINGLE_SHOT,
    GKANIMATION_TYPE_SINGLE_BACK,
    GKANIMATION_TYPE_SINGLE_STAY,
    GKANIMATION_TYPE_OSCILLATE
} animation_type;

typedef struct animation_interface_ {
    void (*on_animate)(animation *a);
} animation_interface;

typedef struct animation_ {
    animation_interface *vtbl;

    guint16 cur_frame;
    guint16 max_frames;
    guint16 frame_step;

    guint16 frame_rate;     // milliseconds
    guint32 old_time;

    gbool is_active;
    gbool is_animating;
    animation_type type;
} animation;

animation *animation_new(animation_type type);
void animation_del(animation *a);
void animation_on_animate(animation *a);
void animation_settype(animation *a, animation_type type);
void animation_setcurrentframe(animation *a, int cur_frame);
void animation_setanimating(animation *a, gbool animating);

GK_STATIC_INLINE guint16 animation_getcurrentframe(animation *a) { return a->cur_frame; }
GK_STATIC_INLINE guint16 animation_getmaxframes(animation *a) { return a->max_frames; }
GK_STATIC_INLINE guint16 animation_getframestep(animation *a) { return a->frame_step; }
GK_STATIC_INLINE guint16 animation_getframerate(animation *a) { return a->frame_rate; }
GK_STATIC_INLINE guint32 animation_getoldtime(animation *a) { return a->old_time; }
GK_STATIC_INLINE gbool animatino_isactive(animation *a) { return a->is_active; }
GK_STATIC_INLINE gbool animation_isanimating(animation *a) { return a->is_animating; }
GK_STATIC_INLINE guint16 animation_gettype(animation *a) { return a->type; }

GK_END_HEADER

#endif // ANIMATION_H
