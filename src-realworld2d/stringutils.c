#include "stringutils.h"

static const guint32 _string_default_capacity = 100;
static const guint32 _string_resize_step = 100;
static const guint32 _string_max_length = GK_MAX_STRING_LEN;


GKString *__Copy(GKString *s) { return GKString_New(strdup(s->_data)); }

static GKStringInterface __vtbl = {
    __Copy
};

GKString *GKString_New(const char *str)
{
    GKString *ret = NULL;
    GK_NEW(ret, GKString);

    ret->vtbl = &__vtbl;
    ret->_length = 0;

    ret->_capacity = _string_default_capacity;
    while (ret->_capacity < strlen(str)) {
        ret->_capacity += _string_resize_step;
        if (ret->_capacity > _string_max_length) {
            GK_BAILOUT("String is too long");
        }
    }
    GK_MALLOC(ret->_data, char, ret->_capacity);

    strcpy(ret->_data, str);
    return ret;
}

int GKChar_IsWhiteSpace(char c) {
    switch (c) {
    case ' ':
    case '\t':
    case '\n':
    case '\v':
    case '\a':
    case '\f':
    case '\r':
        return GKTRUE;
    default:
        return GKFALSE;
    }
}

char *GKString_Trim(char *str)
{
    char *ret = NULL;
    int cont = 1;
    int i = 0;
    int start = 0;
    int end = 0;
    int len = strlen(str);

    while ((cont) && (i < len - 1))
    {
        if (!GKChar_IsWhiteSpace(str[i]))
        {
            start = i;
            cont = 0;
        }
        i++;
    }

    cont = 1;
    i = len - 1;
    while ((cont) && (i >= 0))
    {
        if (!GKChar_IsWhiteSpace(str[i]))
        {
            end = i;
            cont = 0;
        }
        i--;
    }

    if (end <= start)
    {
        GK_NEW(ret, char);
        return ret;
    }

    len = end - start + 1;
    GK_MALLOC(ret, char, len + 1);

    strncpy(ret, str + start, len);

    return ret;
}

char *GKString_ToLower(char *str)
{
    char *ret = GKString_Copy(str);
    char *c = ret;
    for (; *c; ++c)
        *c = tolower(*c);
    return ret;
}

char *GKString_ToUpper(char *str)
{
    char *ret = GKString_Copy(str);
    char *c = ret;
    for (; *c; ++c)
        *c = toupper(*c);
    return ret;
}

int GKString_Assign(char src_str[], const char *str)
{
    return (sprintf(src_str, str));
}

gint16 GKString_RFindFirst(const char *str, char c)
{
    guint16 i = strlen(str) - 1;
    while (i != 0) {
        if (*(str + i) == c) {
            return (i);
        }
        --i;
    }

    return (GK_STR_NOTFOUND);
}

char *GKString_Copy(const char *str) {
    char *str_copyed = strdup(str);
    printf("Allocate 1 block of memory for [%s] (instance of [char *]) at %p\n", str, str);
    return str_copyed;
}

static char *GKConfigPartFromString(char *str, int part)
{
    char *wc = GKString_Copy(str);
    char *eq = strchr(wc, '=');
    char *p = NULL;

    if (eq == NULL)
    {
        GK_DELETE(wc);
        return NULL;
    }

    eq[0] = 0;
    if (part == 0)
    {
        p = GKString_Trim(wc);
    }
    else
    {
        p = GKString_Trim(eq + 1);
    }
    GK_DELETE(wc);
    return p;
}

char *GKConfigNameFromString(char *str)
{
    return GKConfigPartFromString(str, 0);
}

char *GKConfigValueFromString(char *str)
{
    return GKConfigPartFromString(str, 1);
}
