#include <stdio.h>
#include "rect.h"
#include "sprite.h"
#include "charactermotion.h"
#include "character.h"

GKCharacter *GKCharacter_NewFromFile(const char *fn)
{
    guint32 i = 0;
    guint32 states = 0;
    char sprite_config[GK_MAX_FILENAME_LEN];
    FILE *f = NULL;

    GKCharacter *ret = NULL;
    GK_NEW(ret, GKCharacter);

    ret->_curDirection = 0;
    ret->_motion = GKMotion_New(0, 0, GKMOTIONSTATE_RUN);

    f = fopen(fn, "r");
    if (f == NULL) {
        GK_BAILOUT("%s\n", "Fail to read character file.");
    }

    fscanf(f, "%d\n", &states);

    if (states) {
        ret->_directions = states;
        GK_MALLOC(ret->_sprites, GKSprite*, states);
    } else {
        GK_BAILOUT("%s\n", "Invalid state size.");
    }

    for (; i < states; ++i) {
        memset(sprite_config, 0, GK_MAX_FILENAME_LEN);
        fscanf(f, "%s\n", sprite_config);
        ret->_sprites[i] = GKSprite_NewFromConfig(sprite_config);
    }

    return (ret);
}

void GKCharacter_Delete(GKCharacter *c)
{
    guint32 i = 0;
    for (; i < c->_directions; ++i) {
        GKSprite_Delete(c->_sprites[i]);
    }

    GK_DELETE(c);
}

void GKCharacter_Blit(GKCharacter *c, struct GKSurface *s)
{
    assert(c->_curDirection < c->_directions);
    GKMotion_Move(c->_motion);
    GKSprite_SetPosition(c->_sprites[c->_curDirection], c->_motion->_worldX, c->_motion->_worldY);
    GKSprite_Blit(c->_sprites[c->_curDirection], s);
}

void GKCharacter_ChangeState(GKCharacter *c, guint8 state)
{
    if (state >= c->_directions) {
        GK_WARNING("%s\n", "State out of range.");
        c->_curDirection = GKCHARACTER_DIRECTION_EAST;
    } else {
        c->_curDirection = state;
    }
}

void GKCharacter_MoveTo(GKCharacter *c, gint16 x, gint16 y)
{
    GKMotion_SetTarget(c->_motion, x, y);
}

void GKCharacter_SetPosition(GKCharacter *c, gint16 x, gint16 y)
{
    c->_motion->_worldX = x;
    c->_motion->_worldY = y;
}
