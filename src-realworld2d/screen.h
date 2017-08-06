#ifndef SCREEN_H
#define SCREEN_H

#include "globaldefs.h"
#include "surface.h"

GK_BEGIN_HEADER

typedef struct GKScreen {
    struct GKSurface *_surface;
} GKScreen;

GKScreen *GKScreen_Get(void);
struct GKSurface *GKScreen_GetSurface(void);
void GKScreen_Free(void);
void GKScreen_SetVideoMode(gint32 w, gint32 h, gbool full_screen);
int GKScreen_Flip(void);
void GKScreen_ToggleFullScreen(void);
void GKScreen_SetCaption(const char *caption);
void GKScreen_SetIcon(struct GKSurface *surface);
void GKScreen_ShowCursor(void);
void GKScreen_HideCursor(void);

GK_STATIC_INLINE gint32 GKScreen_GetWidth() { return (GKSurface_GetWidth(GKScreen_GetSurface())); }
GK_STATIC_INLINE gint32 GKScreen_GetHeight() { return (GKSurface_GetHeight(GKScreen_GetSurface())); }

GK_END_HEADER

#endif // SCREEN_H
