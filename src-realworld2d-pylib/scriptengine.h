#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

int scriptengine_init(void);

void scriptengine_exit(void);

int scriptengine_runstr(const char *str);

int scriptengine_runfile(const char *file_name);


// capi interface
void capi_load_timer(void);
void capi_load_display(void);
void capi_load_assets(void);
void capi_load_gameevent(void);

//
int assets_loadsurface(const char *file_name);
struct SDL_Surface *assets_getsurface(gint32 key);

GK_END_HEADER

#endif // SCRIPTENGINE_H
