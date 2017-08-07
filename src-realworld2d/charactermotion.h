#ifndef CHARACTERMOTION_H
#define CHARACTERMOTION_H

#include "globaldefs.h"

GK_BEGIN_HEADER

#define MOTION_DEFAULT_RATE 3.0f

typedef enum motion_state_ {
    GKMOTIONSTATE_STAND,
    GKMOTIONSTATE_RUN,
    GKMOTIONSTATE_FIGHTREADY,
    GKMOTIONSTATE_FIGHT,
    GKMOTIONSTATE_DEFEND,
    GKMOTIONSTATE_INJURY,
    GKMOTIONSTATE_DEAD
} motion_state;

typedef struct motion_ {
    gint16 world_x;
    gint16 world_y;
    gint16 target_x;
    gint16 target_y;
    gfloat vx;
    gfloat vy;
    gfloat rate;
    guint8 state;
} motion;

motion *motion_new(gint16 x, gint16 y, guint8 state);
void motion_move(motion *m);

GK_STATIC_INLINE void motion_setvelocity(motion *m, gint16 vx, gint16 vy)
{ m->vx = vx; m->vy = vy; }

GK_STATIC_INLINE void GKMotion_SetTarget(motion *m, gint16 x, gint16 y)
{ m->target_x = x; m->target_y = y; }

GK_END_HEADER

#endif // CHARACTERMOTION_H
