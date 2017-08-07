#ifndef FONT_H
#define FONT_H

#include "globaldefs.h"
#include "graphics.h"

GK_BEGIN_HEADER

typedef struct font_ font;
typedef struct surface_ surface;

typedef struct _TTF_Font TTF_Font;

enum FontRenderType_{
    FONT_SOLID = 0, FONT_BLENDED
};

typedef struct font_interface_ {
    gbool (*open)(font *fnt, const char *file_name, gint32 size);

    void (*render_char)(font *fnt, surface *dst, char c, color_type color, guint8 type);
    void (*render_text)(font *fnt, surface *dst, const char *str, color_type color, guint8 type);
    void (*render_unicodechar)(font *fnt, surface *dst, guint16 c, color_type color, guint8 type);
    void (*render_unicodetext)(font *fnt, surface *dst, const guint16 *str, color_type color, guint8 type);

    gbool (*is_valid)(font *fnt);
    void (*set_style)(font *fnt, guint8 style);

    gint32 (*height)(font *fnt);
    gint32 (*ascent)(font *fnt);
    gint32 (*descent)(font *fnt);
    gint32 (*line_skip)(font *fnt);
} font_interface;

typedef struct font_ {
    font_interface *vtbl;

    TTF_Font *data;
} font;

void fontsystem_init(void);
void fontsystem_quit(void);

font *font_new(void);
void font_del(font *fnt);

GK_END_HEADER

#endif // FONT_H
