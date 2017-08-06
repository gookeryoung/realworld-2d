#ifndef FONT_H
#define FONT_H

#include "globaldefs.h"
#include "graphics.h"

GK_BEGIN_HEADER


typedef struct GKFont_ GKFont;
typedef struct GKSurface GKSurface;

typedef struct _TTF_Font TTF_Font;

enum GKFontRenderType_{
    GKFONT_SOLID = 0, GKFONT_BLENDED
};

typedef struct GKFontInterface_ {
    gbool (*Open)(GKFont *fnt, const char *file_name, gint32 size);

    void (*RenderChar)(GKFont *fnt, GKSurface *dst, char c, color_type color, guint8 type);
    void (*RenderText)(GKFont *fnt, GKSurface *dst, const char *str, color_type color, guint8 type);
    void (*RenderUnicodeChar)(GKFont *fnt, GKSurface *dst, guint16 c, color_type color, guint8 type);
    void (*RenderUnicodeText)(GKFont *fnt, GKSurface *dst, const guint16 *str, color_type color, guint8 type);

    gbool (*IsValid)(GKFont *fnt);
    void (*SetStyle)(GKFont *fnt, guint8 style);

    gint32 (*Height)(GKFont *fnt);
    gint32 (*Ascent)(GKFont *fnt);
    gint32 (*Descent)(GKFont *fnt);
    gint32 (*LineSkip)(GKFont *fnt);
} GKFontInterface;

struct GKFont_ {
    GKFontInterface *vtbl;

    TTF_Font *_font;
};

void GKFontSystem_Init(void);
void GKFontSystem_Quit(void);

GKFont *GKFont_New(void);
void GKFont_Delete(GKFont *fnt);

GK_END_HEADER

#endif // FONT_H
