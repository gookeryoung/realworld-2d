#include "screen.h"
#include "charactermotion.h"

motion *
motion_new(gint16 x, gint16 y, guint8 state) {
    motion *ret = NULL;
    GK_NEW(ret, motion);

    ret->world_x = x;
    ret->world_y = y;
    ret->state = state;

    ret->target_x = -1;
    ret->target_y = -1;

    ret->vx = 0;
    ret->vy = 0;
    ret->rate = MOTION_DEFAULT_RATE;

    return (ret);
}

void
motion_move(motion *m) {
    gfloat dx, dy;
    gfloat adx, ady;
    gfloat distance;
    gfloat vx, vy;

    if (m->target_x < 0 || m->target_y < 0) {
        return;
    }
    if (m->target_x == m->world_x || m->target_y == m->world_y) {
        if (m->state == GKMOTIONSTATE_RUN) {
            m->state = GKMOTIONSTATE_STAND;
        }
        return;
    }

    dx = GK_LENGTH(m->world_x, m->target_x);
    dy = GK_LENGTH(m->world_y, m->target_y);
    adx = fabsf(dx);
    ady = fabsf(dy);
    distance = GK_DISTANCE(m->world_x, m->world_y, m->target_x, m->target_y);
    vx = m->rate * adx / distance + 0.5f;
    vy = m->rate * ady / distance + 0.5f;

    if (GK_FLOAT_EQUAL(adx, 0.0f)) {
        m->vx = 0;
    } else {
        m->vx = dx / adx * vx;
    }

    if (GK_FLOAT_EQUAL(ady, 0.0f)) {
        m->vy = 0;
    } else {
        m->vy = dy / ady * vy;
    }

    if (vx > adx) {
        m->vx = dx;
    }
    if (vy > ady) {
        m->vy = dy;
    }

    m->world_x += m->vx;
    m->world_y += m->vy;

    m->world_x = GK_BOUND(m->world_x, 0, screen_getwidth() - 1);
    m->world_y = GK_BOUND(m->world_y, 0, screen_getheight() - 1);
}

