#ifndef CHARACTERMOTION_H
#define CHARACTERMOTION_H

#include "globaldefs.h"

GK_BEGIN_HEADER

#define GKMOTION_DEFAULT_RATE 3.0f

typedef enum GKMotionState {
    GKMOTIONSTATE_STAND,
    GKMOTIONSTATE_RUN,
    GKMOTIONSTATE_FIGHTREADY,
    GKMOTIONSTATE_FIGHT,
    GKMOTIONSTATE_DEFEND,
    GKMOTIONSTATE_INJURY,
    GKMOTIONSTATE_DEAD
} GKMotionState;

typedef struct GKMotion {
    gint16 _worldX;
    gint16 _worldY;
    gint16 _targetX;
    gint16 _targetY;
    gfloat _vx;
    gfloat _vy;
    gfloat _rate;
    guint8 _state;
} GKMotion;

GKMotion *GKMotion_New(gint16 x, gint16 y, guint8 state);
void GKMotion_Move(GKMotion *m);

static __inline void GKMotion_SetV(GKMotion *m, gint16 vx, gint16 vy)
{ m->_vx = vx; m->_vy = vy; }

static __inline void GKMotion_SetTarget(GKMotion *m, gint16 x, gint16 y)
{ m->_targetX = x; m->_targetY = y; }

GK_END_HEADER

#endif // CHARACTERMOTION_H
