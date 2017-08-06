#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct GKStringInterface_ GKStringInterface;

#define GK_STR_NOTFOUND -1

typedef struct GKString_ {
    guint32 _length;
    guint32 _capacity;

    char *_data;
    GKStringInterface *vtbl;
} GKString;

typedef struct GKStringInterface_ {
    GKString *(*Copy)(GKString *);
} GKStringInterface;

GKString *GKString_New(const char *str);

int GKChar_IsWhiteSpace(char c);
char *GKString_Trim(char *str);
char *GKString_ToLower(char *str);
char *GKString_ToUpper(char *str);
int GKString_Assign(char src_str[], const char *str);
gint16 GKString_RFindFirst(const char *str, char c);
char *GKString_Copy(const char *str);

char *GKConfigNameFromString(char *str);
char *GKConfigValueFromString(char *str);

GK_END_HEADER

#endif // STRINGUTILS_H
