#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

void scriptengine_init(void);

void scriptengine_exit(void);

int scriptengine_runstr(const char *str);

int scriptengine_runfile(const char *file_name);

#endif // SCRIPTENGINE_H
