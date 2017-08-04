#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

void scriptengine_init(void);

void scriptengine_exit(void);

int scriptengine_runstr(const char *str);

int scriptengine_runfile(const char *file_name);


// capi interface
void capi_load_timer(void);

#endif // SCRIPTENGINE_H
