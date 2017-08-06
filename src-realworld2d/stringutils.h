#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct string_interface_ string_interface;

#define GK_STR_NOTFOUND -1

typedef struct string_ {
    guint32 length;
    guint32 capacity;

    char *data;
    string_interface *vtbl;
} string;

typedef struct string_interface_ {
    string *(*Copy)(string *);
} string_interface;

string *string_new(const char *str);
char *string_trim(char *str);
char *string_tolower(char *str);
char *string_toupper(char *str);
int string_assign(char src_str[], const char *str);
gint16 string_rfindfirst(const char *str, char c);
char *string_copy(const char *str);

char *configname_fromstring(char *str);
char *configvalue_fromstring(char *str);

GK_END_HEADER

#endif // STRINGUTILS_H
