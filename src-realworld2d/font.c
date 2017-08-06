#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "surface.h"
#include "font.h"

static gbool __Open(GKFont *fnt, const char *file_name, gint32 size);

static void __RenderChar(GKFont *fnt, GKSurface *dst, char c, color_type color, guint8 type);
static void __RenderText(GKFont *fnt, GKSurface *dst, const char *str, color_type color, guint8 type);
static void __RenderUnicodeChar(GKFont *fnt, GKSurface *dst, guint16 c, color_type color, guint8 type);
static void __RenderUnicodeText(GKFont *fnt, GKSurface *dst, const guint16 *str, color_type color, guint8 type);

GK_STATIC_INLINE gbool __IsValid(GKFont *fnt) { return fnt->_font != NULL; }

GK_STATIC_INLINE void __SetStyle(GKFont *fnt, guint8 style)
{ if (fnt->_font) TTF_SetFontStyle(fnt->_font, style); }

GK_STATIC_INLINE gint32 __Height(GKFont *fnt)
{ return (fnt->_font ? TTF_FontHeight(fnt->_font) : 0); }

GK_STATIC_INLINE gint32 __Ascent(GKFont *fnt)
{ return (fnt->_font ? TTF_FontAscent(fnt->_font) : 0); }

GK_STATIC_INLINE gint32 __Descent(GKFont *fnt)
{ return (fnt->_font ? TTF_FontDescent(fnt->_font) : 0); }

GK_STATIC_INLINE gint32 __LineSkip(GKFont *fnt)
{ return (fnt->_font ? TTF_FontLineSkip(fnt->_font) : 0); }

static gbool __initialized = GKFALSE;

static GKFontInterface __vtbl = {
    __Open,
    __RenderChar,
    __RenderText,
    __RenderUnicodeChar,
    __RenderUnicodeText,

    __IsValid,
    __SetStyle,

    __Height,
    __Ascent,
    __Descent,
    __LineSkip
};

GKFont *GKFont_New(void)
{
    GKFont *ret = NULL;
    GK_NEW(ret, GKFont);

    ret->vtbl = &__vtbl;
    ret->_font = NULL;

    return ret;
}

void GKFont_Delete(GKFont *fnt) { if (fnt) { TTF_CloseFont(fnt->_font); } }

void GKFontSystem_Init(void)
{
    GK_REQUIRE(TTF_Init() != -1, "Font initialize failed.");
    __initialized = GKTRUE;
}

void GKFontSystem_Quit(void)
{
    TTF_Quit();
    __initialized = GKFALSE;
}

static gbool __Open(GKFont *fnt, const char *file_name, gint32 size)
{
    if (__initialized) {
        if (fnt->_font) {
            TTF_CloseFont(fnt->_font);
        }
        fnt->_font = TTF_OpenFont(file_name, size);

        GK_CHECK(fnt->_font, "Open file %s failed.", file_name);
    } else {
        GK_BAILOUT("Font system not initialized.");
    }

    return (fnt->_font != NULL);
}

static void __RenderChar(GKFont *fnt, GKSurface *dst, char c, color_type color, guint8 type)
{
    char buffer[2] = { '\0', '\0' };
    buffer[0] = c;

    __RenderText(fnt, dst, buffer, color, type);
}

static void __RenderText(GKFont *fnt, GKSurface *dst, const char *str, color_type color, guint8 type)
{
    GK_REQUIRE(type == GKFONT_SOLID || GKFONT_BLENDED, "Font render type error.");

    if (dst->_data) {
        SDL_FreeSurface(dst->_data);
    }

    if (fnt->_font) {
        switch (type) {
        case GKFONT_BLENDED:
            dst->_data = TTF_RenderUTF8_Blended(fnt->_font, str, color);
            break;
        default:
            dst->_data = TTF_RenderUTF8_Solid(fnt->_font, str, color);
            break;
        }
    }
}

static void __RenderUnicodeChar(GKFont *fnt, GKSurface *dst, guint16 c, color_type color, guint8 type)
{
    guint16 buffer[2] = { L'\0', L'\0' };
    buffer[0] = c;

    __RenderUnicodeText(fnt, dst, buffer, color, type);
}

static void __RenderUnicodeText(GKFont *fnt, GKSurface *dst, const guint16 *str, color_type color, guint8 type)
{
    GK_REQUIRE(type == GKFONT_SOLID || GKFONT_BLENDED, "Font render type error.");

    if (dst->_data) {
        SDL_FreeSurface(dst->_data);
    }

    if (fnt->_font) {
        switch (type) {
        case GKFONT_BLENDED:
            dst->_data = TTF_RenderUNICODE_Blended(fnt->_font, str, color);
            break;
        default:
            dst->_data = TTF_RenderUNICODE_Solid(fnt->_font, str, color);
            break;
        }
    }
}
