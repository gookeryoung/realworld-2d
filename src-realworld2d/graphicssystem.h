#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct graphics_system_ {
    int fps;
    struct timer_ *timer;
} graphics_system;

graphics_system *graphicssytem_get(void);
void graphicssystem_del(void);
void graphicssystem_delay(void);

GK_END_HEADER

#endif // GRAPHICSSYSTEM_H
