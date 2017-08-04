#ifndef TIMER_H
#define TIMER_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct timer_ {
    gint32 start_tick;
    gint32 pause_tick;

    gbool is_paused;
    gbool is_started;
} timer;

timer *timer_new(void);
void timer_del(timer *t);
void timer_start(timer *t);
void timer_reset(timer *t);
void timer_pause(timer *t);
void timer_stop(timer *t);
gint32 timer_getticks(timer *t);

#define timer_ispaused(t) ((t)->is_paused)
#define timer_isstarted(t) ((t)->is_started)
#define timer_getstarttick(t) ((t)->start_tick)
#define timer_getpausetick(t) ((t)->pause_tick)

GK_END_HEADER

#endif // TIMER_H
