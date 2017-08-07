#include <stdio.h>
#include "rect.h"
#include "sprite.h"
#include "charactermotion.h"
#include "character.h"

character *
character_new_fromfile(const char *file_name) {
    guint32 i = 0;
    guint32 states = 0;
    char sprite_config[GK_MAX_FILENAME_LEN];
    FILE *f = NULL;

    character *ret = NULL;
    GK_NEW(ret, character);

    ret->cur_direction = 0;
    ret->motion = motion_new(0, 0, GKMOTIONSTATE_RUN);

    f = fopen(file_name, "r");
    if (f == NULL) {
        GK_BAILOUT("%s\n", "Fail to read character file.");
    }

    fscanf(f, "%d\n", &states);

    if (states) {
        ret->directions = states;
        GK_MALLOC(ret->sprites, sprite*, states);
    } else {
        GK_BAILOUT("%s\n", "Invalid state size.");
    }

    for (; i < states; ++i) {
        memset(sprite_config, 0, GK_MAX_FILENAME_LEN);
        fscanf(f, "%s\n", sprite_config);
        ret->sprites[i] = sprite_new_fromfile(sprite_config);
    }

    return (ret);
}

void
character_del(character *c) {
    guint32 i = 0;
    for (; i < c->directions; ++i) {
        sprite_del(c->sprites[i]);
    }
    GK_DELETE(c);
}

void
character_blit(character *c, struct surface_ *s) {
    assert(c->cur_direction < c->directions);
    motion_move(c->motion);
    sprite_setposition(c->sprites[c->cur_direction], c->motion->world_x, c->motion->world_y);
    sprite_blit(c->sprites[c->cur_direction], s);
}

void
character_changestate(character *c, guint8 state) {
    if (state >= c->directions) {
        GK_WARNING("%s\n", "State out of range.");
        c->cur_direction = GKCHARACTER_DIRECTION_EAST;
    } else {
        c->cur_direction = state;
    }
}

void
character_moveto(character *c, gint16 x, gint16 y) {
    GKMotion_SetTarget(c->motion, x, y);
}

void
character_setposition(character *c, gint16 x, gint16 y) {
    c->motion->world_x = x;
    c->motion->world_y = y;
}
