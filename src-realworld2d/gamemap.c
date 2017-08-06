#include <stdlib.h>
#include "surface.h"
#include "sprite.h"
#include "stringutils.h"
#include "gamemapground.h"
#include "gamemap.h"

GKMapObject *GKMapObject_New(const char *config_str)
{
    gint32 x, y;
    char data_file_path[GK_MAX_FILENAME_LEN];

    GKMapObject *ret = NULL;
    GK_NEW(ret, GKMapObject);

    memset(ret->_name, 0, GKMAPOBJECT_NAME_LENGTH);
    memset(data_file_path, 0, GK_MAX_FILENAME_LEN);

    sscanf(config_str,
           "%d,%d,%d,%d,%d %s\n",
           &ret->_type,
           &ret->_id,
           &ret->_depth,
           &x,
           &y,
           data_file_path);

    if (ret->_type == GKMAPOBJECT_STATIC) {
        ret->_data = GKSurface_NewFromFile(data_file_path, GKFALSE);
        GKSurface_SetColorkey(ret->_data, 255, 255, 255);
        GKSurface_SetPosition(ret->_data, x, y);
    } else if (ret->_type == GKMAPOBJECT_ANIMATED) {
        ret->_data = GKSprite_NewFromConfig(data_file_path);
        GKSprite_SetPosition(ret->_data, x, y);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }

    return (ret);
}

void GKMapObject_Delete(GKMapObject *m)
{
    if (m->_type == GKMAPOBJECT_STATIC) {
        GKSurface_Delete(m->_data);
    } else if (m->_type == GKMAPOBJECT_ANIMATED) {
        GKSprite_Delete(m->_data);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }

    GK_DELETE(m);
}

void GKMapObject_Blit(GKMapObject *m, struct GKSurface *s)
{
    if (m->_type == GKMAPOBJECT_STATIC) {
        GKSurface_Blit(m->_data, s);
    } else if (m->_type == GKMAPOBJECT_ANIMATED) {
        GKSprite_Blit(m->_data, s);
    } else {
        GK_BAILOUT("%s\n","The type of map object doesn't exist.");
    }
}

GKMap *GKMap_New(void)
{
    GKMap *ret = NULL;
    GK_NEW(ret, GKMap);

    ret->_id = 0;
    GKString_Assign(ret->_name, " ");

    ret->_prev = NULL;
    ret->_next = NULL;
    ret->_enterPt.x = 0;
    ret->_enterPt.y = 0;
    ret->_exitPt.x = 0;
    ret->_exitPt.y = 0;

    ret->_objectCount = 0;
    GK_MALLOC(ret->_objects, GKMapObject*, ret->_objectCount);

    return (ret);
}

GKMap *GKMap_NewFromFile(const char *fn)
{
    guint16 i = 0;
    FILE *f = NULL;
    char mapobj_config_str[GK_MAX_FILENAME_LEN];
    char background_file_name[GK_MAX_FILENAME_LEN];

    GKMap *ret = NULL;
    GK_NEW(ret, GKMap);

    memset(background_file_name, 0, GK_MAX_FILENAME_LEN);

    f = fopen(fn, "r");
    if (f == NULL) {
        GK_BAILOUT("%s\n", "Fail to read background file.");
    }

    fscanf(f, "%s\n", background_file_name);

    ret->_ground = GKGround_NewFromFile(background_file_name);
    fscanf(f, "%d\n", &ret->_objectCount);

    GK_MALLOC(ret->_objects, GKMapObject*, ret->_objectCount);

    for (i = 0; i < ret->_objectCount; ++i) {
        memset(mapobj_config_str, 0, GK_MAX_FILENAME_LEN);
        fgets(mapobj_config_str, GK_MAX_FILENAME_LEN, f);
        ret->_objects[i] = GKMapObject_New(mapobj_config_str);
    }

    return (ret);
}

void GKMap_Delete(GKMap *m)
{
    guint16 i;
    for (i = 0; i < m->_objectCount; ++i) {
        GKMapObject_Delete(m->_objects[i]);
    }

    GKGround_Delete(m->_ground);
    GK_DELETE(m);
}

void GKMap_Blit(GKMap *m, struct GKSurface *s)
{
    guint16 i = 0;

    GKGround_Blit(m->_ground, s);

    for (i = 0; i < m->_objectCount; ++i) {
        GKMapObject_Blit(m->_objects[i], s);
    }
}

void GKMap_Append(GKMap *m, GKMap *next)
{
    m->_next = next;
    next->_prev = m;
}
