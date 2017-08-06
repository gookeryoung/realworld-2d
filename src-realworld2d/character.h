#ifndef CHARACTER_H
#define CHARACTER_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef enum character_direction_state_{
    GKCHARACTER_DIRECTION_EAST ,
    GKCHARACTER_DIRECTION_SOUTHEAST,
    GKCHARACTER_DIRECTION_SOUTH,
    GKCHARACTER_DIRECTION_SOUTHWEST,
    GKCHARACTER_DIRECTION_WEST,
    GKCHARACTER_DIRECTION_NORTHWEST,
    GKCHARACTER_DIRECTION_NORTH,
    GKCHARACTER_DIRECTION_NORTHEAST
} character_direction_state;

typedef struct character_ {
    guint8 cur_direction;
    guint8 directions;
    struct sprite_ **sprites;

    struct motion_ *motion;
} character;

character *character_new_fromfile(const char *file_name);
void character_del(character *c);
void character_blit(character *c, struct surface_ *s);
void character_changestate(character *c, guint8 state);
void character_moveto(character *c, gint16 x, gint16 y);

void character_setposition(character *c, gint16 x, gint16 y);

GK_END_HEADER

#endif // CHARACTER_H
