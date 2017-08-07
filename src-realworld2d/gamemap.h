#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "globaldefs.h"
#include "rect.h"

GK_BEGIN_HEADER

#define MAPOBJECT_NAME_LENGTH   64
#define MAP_NAME_LENGTH         36

enum {
    MAPOBJECT_STATIC = 1,
    MAPOBJECT_ANIMATED
};

typedef struct gamemap_object_ {
    char name[MAPOBJECT_NAME_LENGTH];
    guint32 id;
    guint32 type;       /* Define static or moving object. */
    guint32 depth;      /* Determines the blit order. */

    void *data;
} gamemap_object;

gamemap_object *gamemapobject_new(const char *config_str);
void gamemapobject_del(gamemap_object *m);
void gamemapobject_blit(gamemap_object *m, struct surface_ *s);

typedef struct gamemap_ {
    guint16 id;
    char name[MAP_NAME_LENGTH];

    struct gamemap_ *prev;
    struct gamemap_ *next;

    point2d enter_point;
    point2d exit_point;

    struct gamemap_object_ **objects;
    guint32 object_count;

    struct ground_ *ground;
} gamemap;

gamemap *gamemap_new(void);
gamemap *gamemap_new_fromfile(const char *fn);
void gamemap_del(gamemap *m);
void gamemap_blit(gamemap *m, struct surface_ *s);
void gamemap_append(gamemap *m, gamemap *next);

GK_END_HEADER

#endif // GAMEMAP_H
