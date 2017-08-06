#include <stdlib.h>
#include "surface.h"
#include "sprite.h"
#include "stringutils.h"
#include "gamemapground.h"
#include "gamemap.h"

gamemap_object *
gamemapobject_new(const char *config_str) {
    gint32 x, y;
    char data_file_path[GK_MAX_FILENAME_LEN];

    gamemap_object *ret = NULL;
    GK_NEW(ret, gamemap_object);

    memset(ret->name, 0, MAPOBJECT_NAME_LENGTH);
    memset(data_file_path, 0, GK_MAX_FILENAME_LEN);

    sscanf(config_str,
           "%d,%d,%d,%d,%d %s\n",
           &ret->type,
           &ret->id,
           &ret->depth,
           &x,
           &y,
           data_file_path);

    if (ret->type == MAPOBJECT_STATIC) {
        ret->data = surface_new_fromfile(data_file_path, GKFALSE);
        surface_setcolorkey(ret->data, 255, 255, 255);
        surface_setposition(ret->data, x, y);
    } else if (ret->type == MAPOBJECT_ANIMATED) {
        ret->data = sprite_new_fromfile(data_file_path);
        sprite_setposition(ret->data, x, y);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }

    return (ret);
}

void
gamemapobject_del(gamemap_object *m) {
    if (m->type == MAPOBJECT_STATIC) {
        surface_del(m->data);
    } else if (m->type == MAPOBJECT_ANIMATED) {
        sprite_del(m->data);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }

    GK_DELETE(m);
}

void
gamemapobject_blit(gamemap_object *m, struct surface_ *s) {
    if (m->type == MAPOBJECT_STATIC) {
        surface_blit(m->data, s);
    } else if (m->type == MAPOBJECT_ANIMATED) {
        sprite_blit(m->data, s);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }
}

gamemap *
gamemap_new(void) {
    gamemap *ret = NULL;
    GK_NEW(ret, gamemap);

    ret->id = 0;
    string_assign(ret->name, " ");

    ret->prev = NULL;
    ret->next = NULL;
    ret->enter_point.x = 0;
    ret->enter_point.y = 0;
    ret->exit_point.x = 0;
    ret->exit_point.y = 0;

    ret->object_count = 0;
    GK_MALLOC(ret->objects, gamemap_object*, ret->object_count);

    return (ret);
}

gamemap *
gamemap_new_fromfile(const char *fn) {
    guint16 i = 0;
    FILE *f = NULL;
    char mapobj_config_str[GK_MAX_FILENAME_LEN];
    char background_file_name[GK_MAX_FILENAME_LEN];

    gamemap *ret = NULL;
    GK_NEW(ret, gamemap);

    memset(background_file_name, 0, GK_MAX_FILENAME_LEN);

    f = fopen(fn, "r");
    if (f == NULL) {
        GK_BAILOUT("%s\n", "Fail to read background file.");
    }

    fscanf(f, "%s\n", background_file_name);

    ret->ground = ground_new_fromfile(background_file_name);
    fscanf(f, "%d\n", &ret->object_count);

    GK_MALLOC(ret->objects, gamemap_object*, ret->object_count);

    for (i = 0; i < ret->object_count; ++i) {
        memset(mapobj_config_str, 0, GK_MAX_FILENAME_LEN);
        fgets(mapobj_config_str, GK_MAX_FILENAME_LEN, f);
        ret->objects[i] = gamemapobject_new(mapobj_config_str);
    }

    return (ret);
}

void
gamemap_del(gamemap *m) {
    guint16 i;
    for (i = 0; i < m->object_count; ++i) {
        gamemapobject_del(m->objects[i]);
    }

    ground_del(m->ground);
    GK_DELETE(m);
}

void
gamemap_blit(gamemap *m, struct surface_ *s) {
    guint16 i = 0;

    ground_blit(m->ground, s);

    for (i = 0; i < m->object_count; ++i) {
        gamemapobject_blit(m->objects[i], s);
    }
}

void
gamemap_append(gamemap *m, gamemap *next) {
    m->next = next;
    next->prev = m;
}
