#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct GKGraphicsSystem {
    int _fps;
    struct timer_ *_timer;
} GKGraphicsSystem;

GKGraphicsSystem *GKGraphicsSystem_Get(void);
void GKGraphicsSystem_Free(void);
void GKGraphicsSystem_Delay(void);
guint32 GKGraphicsSystem_GetFPS(void);

GK_END_HEADER

#endif // GRAPHICSSYSTEM_H
