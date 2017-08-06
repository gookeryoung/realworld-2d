#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "surface.h"
#include "font.h"

static gbool _open(font *fnt, const char *file_name, gint32 size);

static void _render_char(font *fnt, surface *dst, char c, color_type color, guint8 type);
static void _render_text(font *fnt, surface *dst, const char *str, color_type color, guint8 type);
static void _render_unicodechar(font *fnt, surface *dst, guint16 c, color_type color, guint8 type);
static void _render_unicodetext(font *fnt, surface *dst, const guint16 *str, color_type color, guint8 type);

GK_STATIC_INLINE gbool _isvalid(font *fnt) { return fnt->data != NULL; }

GK_STATIC_INLINE void _setstyle(font *fnt, guint8 style)
{ if (fnt->data) TTF_SetFontStyle(fnt->data, style); }

GK_STATIC_INLINE gint32 _height(font *fnt)
{ return (fnt->data ? TTF_FontHeight(fnt->data) : 0); }

GK_STATIC_INLINE gint32 _ascent(font *fnt)
{ return (fnt->data ? TTF_FontAscent(fnt->data) : 0); }

GK_STATIC_INLINE gint32 _descent(font *fnt)
{ return (fnt->data ? TTF_FontDescent(fnt->data) : 0); }

GK_STATIC_INLINE gint32 _lineskip(font *fnt)
{ return (fnt->data ? TTF_FontLineSkip(fnt->data) : 0); }

static gbool _is_initialized = GKFALSE;

static font_interface _vtbl = {
    _open,
    _render_char,
    _render_text,
    _render_unicodechar,
    _render_unicodetext,

    _isvalid,
    _setstyle,

    _height,
    _ascent,
    _descent,
    _lineskip
};

font *
font_new(void) {
    font *ret = NULL;
    GK_NEW(ret, font);

    ret->vtbl = &_vtbl;
    ret->data = NULL;

    return ret;
}

void font_del(font *fnt) { if (fnt) { TTF_CloseFont(fnt->data); } }

void
fontsystem_init(void) {
    GK_REQUIRE(TTF_Init() != -1, "Font initialize failed.");
    _is_initialized = GKTRUE;
}

void
fontsystem_quit(void) {
    TTF_Quit();
    _is_initialized = GKFALSE;
}

static gbool
_open(font *fnt, const char *file_name, gint32 size) {
    if (_is_initialized) {
        if (fnt->data) {
            TTF_CloseFont(fnt->data);
        }
        fnt->data = TTF_OpenFont(file_name, size);

        GK_CHECK(fnt->data, "Open file %s failed.", file_name);
    } else {
        GK_BAILOUT("Font system not initialized.");
    }

    return (fnt->data != NULL);
}

static void
_render_char(font *fnt, surface *dst, char c, color_type color, guint8 type) {
    char buffer[2] = { '\0', '\0' };
    buffer[0] = c;

    _render_text(fnt, dst, buffer, color, type);
}

static void
_render_text(font *fnt, surface *dst, const char *str, color_type color, guint8 type) {
    GK_REQUIRE(type == FONT_SOLID || FONT_BLENDED, "Font render type error.");

    if (dst->data) {
        SDL_FreeSurface(dst->data);
    }

    if (fnt->data) {
        switch (type) {
        case FONT_BLENDED:
            dst->data = TTF_RenderUTF8_Blended(fnt->data, str, color);
            break;
        default:
            dst->data = TTF_RenderUTF8_Solid(fnt->data, str, color);
            break;
        }
    }
}

static void
_render_unicodechar(font *fnt, surface *dst, guint16 c, color_type color, guint8 type) {
    guint16 buffer[2] = { L'\0', L'\0' };
    buffer[0] = c;

    _render_unicodetext(fnt, dst, buffer, color, type);
}

static void
_render_unicodetext(font *fnt, surface *dst, const guint16 *str, color_type color, guint8 type) {
    GK_REQUIRE(type == FONT_SOLID || FONT_BLENDED, "Font render type error.");

    if (dst->data) {
        SDL_FreeSurface(dst->data);
    }

    if (fnt->data) {
        switch (type) {
        case FONT_BLENDED:
            dst->data = TTF_RenderUNICODE_Blended(fnt->data, str, color);
            break;
        default:
            dst->data = TTF_RenderUNICODE_Solid(fnt->data, str, color);
            break;
        }
    }
}
