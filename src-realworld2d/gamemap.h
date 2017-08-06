#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "globaldefs.h"
#include "rect.h"

GK_BEGIN_HEADER

#define GKMAPOBJECT_NAME_LENGTH 64
#define GKMAP_NAME_LENGTH       36

enum {
    GKMAPOBJECT_STATIC = 1,
    GKMAPOBJECT_ANIMATED
};

typedef struct GKMapObject {
    char _name[GKMAPOBJECT_NAME_LENGTH];
    guint32 _id;
    guint32 _type;       /* Define static or moving object. */
    guint32 _depth;      /* Determines the blit order. */

    void *_data;
} GKMapObject;

GKMapObject *GKMapObject_New(const char *config_str);
void GKMapObject_Delete(GKMapObject *m);
void GKMapObject_Blit(GKMapObject *m, struct GKSurface *s);

typedef struct GKMap {
    guint16 _id;
    char _name[GKMAP_NAME_LENGTH];

    struct GKMap *_prev;
    struct GKMap *_next;

    point2d _enterPt;
    point2d _exitPt;

    struct GKMapObject **_objects;
    guint32 _objectCount;

    struct GKGround *_ground;
} GKMap;

GKMap *GKMap_New(void);
GKMap *GKMap_NewFromFile(const char *fn);
void GKMap_Delete(GKMap *m);
void GKMap_Blit(GKMap *m, struct GKSurface *s);
void GKMap_Append(GKMap *m, GKMap *next);

GK_END_HEADER

#endif // GAMEMAP_H
