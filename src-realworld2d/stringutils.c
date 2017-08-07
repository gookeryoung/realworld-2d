#include "stringutils.h"

static const guint32 _default_capacity = 100;
static const guint32 _resize_step = 100;
static const guint32 _max_length = GK_MAX_STRING_LEN;


string *_copy(string *s) { return string_new(strdup(s->data)); }

static string_interface __vtbl = {
    _copy
};

string *
string_new(const char *str) {
    string *ret = NULL;
    GK_NEW(ret, string);

    ret->vtbl = &__vtbl;
    ret->length = 0;

    ret->capacity = _default_capacity;
    while (ret->capacity < strlen(str)) {
        ret->capacity += _resize_step;
        if (ret->capacity > _max_length) {
            GK_BAILOUT("String is too long");
        }
    }
    GK_MALLOC(ret->data, char, ret->capacity);

    strcpy(ret->data, str);
    return ret;
}

int
_char_is_whitespace(char c) {
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

char *
string_trim(char *str) {
    char *ret = NULL;
    int cont = 1;
    int i = 0;
    int start = 0;
    int end = 0;
    int len = strlen(str);

    while ((cont) && (i < len - 1)) {
        if (!_char_is_whitespace(str[i])) {
            start = i;
            cont = 0;
        }
        i++;
    }

    cont = 1;
    i = len - 1;
    while ((cont) && (i >= 0)) {
        if (!_char_is_whitespace(str[i])) {
            end = i;
            cont = 0;
        }
        i--;
    }

    if (end <= start) {
        GK_NEW(ret, char);
        return ret;
    }

    len = end - start + 1;
    GK_MALLOC(ret, char, len + 1);

    strncpy(ret, str + start, len);

    return ret;
}

char *
string_tolower(char *str) {
    char *ret = string_copy(str);
    char *c = ret;

    for (; *c; ++c) {
        *c = tolower(*c);
    }

    return ret;
}

char *
string_toupper(char *str) {
    char *ret = string_copy(str);
    char *c = ret;
    for (; *c; ++c)
        *c = toupper(*c);
    return ret;
}

int
string_assign(char src_str[], const char *str) {
    return (sprintf(src_str, str));
}

gint16
string_rfindfirst(const char *str, char c) {
    guint16 i = strlen(str) - 1;
    while (i != 0) {
        if (*(str + i) == c) {
            return (i);
        }
        --i;
    }

    return (GK_STR_NOTFOUND);
}

char *
string_copy(const char *str) {
    char *str_copyed = strdup(str);
    printf("Allocate 1 block of memory for [%s] (instance of [char *]) at %p\n", str, str);
    return str_copyed;
}

static char *
_configpart_fromstring(char *str, int part) {
    char *wc = string_copy(str);
    char *eq = strchr(wc, '=');
    char *p = NULL;

    if (eq == NULL) {
        GK_DELETE(wc);
        return NULL;
    }

    eq[0] = 0;
    if (part == 0) {
        p = string_trim(wc);
    } else {
        p = string_trim(eq + 1);
    }
    GK_DELETE(wc);
    return p;
}

char *
configname_fromstring(char *str) {
    return _configpart_fromstring(str, 0);
}

char *
configvalue_fromstring(char *str) {
    return _configpart_fromstring(str, 1);
}
