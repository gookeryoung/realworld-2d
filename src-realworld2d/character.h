#ifndef CHARACTER_H
#define CHARACTER_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef enum GKCharacterDirectionState{
    GKCHARACTER_DIRECTION_EAST ,
    GKCHARACTER_DIRECTION_SOUTHEAST,
    GKCHARACTER_DIRECTION_SOUTH,
    GKCHARACTER_DIRECTION_SOUTHWEST,
    GKCHARACTER_DIRECTION_WEST,
    GKCHARACTER_DIRECTION_NORTHWEST,
    GKCHARACTER_DIRECTION_NORTH,
    GKCHARACTER_DIRECTION_NORTHEAST
} GKCharacterDirectionState;

typedef struct GKCharacter {
    guint8 _curDirection;
    guint8 _directions;
    struct GKSprite **_sprites;

    struct GKMotion *_motion;
} GKCharacter;

GKCharacter *GKCharacter_NewFromFile(const char *fn);
void GKCharacter_Delete(GKCharacter *c);
void GKCharacter_Blit(GKCharacter *c, struct GKSurface *s);
void GKCharacter_ChangeState(GKCharacter *c, guint8 state);
void GKCharacter_MoveTo(GKCharacter *c, gint16 x, gint16 y);

void GKCharacter_SetPosition(GKCharacter *c, gint16 x, gint16 y);

GK_END_HEADER

#endif // CHARACTER_H
