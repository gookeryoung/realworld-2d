#include "screen.h"
#include "charactermotion.h"

GKMotion *GKMotion_New(gint16 x, gint16 y, guint8 state)
{
    GKMotion *ret = NULL;
    GK_NEW(ret, GKMotion);

    ret->_worldX = x;
    ret->_worldY = y;
    ret->_state = state;

    ret->_targetX = -1;
    ret->_targetY = -1;

    ret->_vx = 0;
    ret->_vy = 0;
    ret->_rate = GKMOTION_DEFAULT_RATE;

    return (ret);
}

void GKMotion_Move(GKMotion *m)
{
    gfloat dx, dy;
    gfloat adx, ady;
    gfloat distance;
    gfloat vx, vy;

    if (m->_targetX < 0 || m->_targetY < 0) {
        return;
    }
    if (m->_targetX == m->_worldX || m->_targetY == m->_worldY) {
        if (m->_state == GKMOTIONSTATE_RUN) {
            m->_state = GKMOTIONSTATE_STAND;
        }
        return;
    }

    dx = GK_LENGTH(m->_worldX, m->_targetX);
    dy = GK_LENGTH(m->_worldY, m->_targetY);
    adx = fabsf(dx);
    ady = fabsf(dy);
    distance = GK_DISTANCE(m->_worldX, m->_worldY, m->_targetX, m->_targetY);
    vx = m->_rate * adx / distance + 0.5f;
    vy = m->_rate * ady / distance + 0.5f;

    if (GK_FLOAT_EQUAL(adx, 0.0f)) {
        m->_vx = 0;
    } else {
        m->_vx = dx / adx * vx;
    }

    if (GK_FLOAT_EQUAL(ady, 0.0f)) {
        m->_vy = 0;
    } else {
        m->_vy = dy / ady * vy;
    }

    if (vx > adx) {
        m->_vx = dx;
    }
    if (vy > ady) {
        m->_vy = dy;
    }

    m->_worldX += m->_vx;
    m->_worldY += m->_vy;

    m->_worldX = GK_BOUND(m->_worldX, 0, GKScreen_GetWidth() - 1);
    m->_worldY = GK_BOUND(m->_worldY, 0, GKScreen_GetHeight() - 1);
}

