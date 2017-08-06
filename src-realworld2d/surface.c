#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphics.h"
#include "palette.h"
#include "surface.h"

static guint8 __GKSurface_Default_Depth__ = 16;
static guint8 __GKSurface_Default_CollisionColor_LowerBound_ = 200;

GKPixel *GKPixel_New(guint8 r, guint8 g, guint8 b, guint8 a)
{
    GKPixel *ret = NULL;
    GK_NEW(ret, GKPixel);

    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;

    return (ret);
}

void GKPixel_Delete(GKPixel *p)
{
    GK_DELETE(p);
}

GKSurface *GKSurface_New(void)
{
    GKSurface *ret = NULL;
    GK_NEW(ret, GKSurface);

    ret->_data = NULL;
    ret->_useAlpha = GKFALSE;
    ret->_cx = 0;
    ret->_cy = 0;

    return (ret);
}

GKSurface *GKSurface_NewFromFile(const char *file_name, gbool use_alpha)
{
    SDL_Surface *loaded = NULL;
    GKSurface *ret = NULL;
    GK_NEW(ret, GKSurface);

    ret->_useAlpha = use_alpha;

    loaded = IMG_Load(file_name);
    if (loaded != NULL) {
        ret->_data = use_alpha ? SDL_DisplayFormatAlpha(loaded) : SDL_DisplayFormat(loaded);
        SDL_FreeSurface(loaded);
    } else {
        GK_BAILOUT("Failed loading surface [%s]: [%s]", file_name, IMG_GetError());
    }

    ret->_cx = ret->_data->w / 2;
    ret->_cy = ret->_data->h / 2;

    return (ret);
}

GKSurface *GKSurface_NewEmptySurface(guint16 w, guint16 h, guint8 depth, guint32 flag)
{
    guint32 rmask = 0;
    guint32 gmask = 0;
    guint32 bmask = 0;
    guint32 amask = 0;

    GKSurface *ret = NULL;
    GK_NEW(ret, GKSurface);

    switch (depth)
    {
    case 32:
        rmask = RMASK32;
        gmask = GMASK32;
        bmask = BMASK32;
        amask = SDL_SRCALPHA & flag ? AMASK32 : 0;
        break;
    case 24:
        rmask = RMASK24;
        gmask = GMASK24;
        bmask = BMASK24;
        amask = SDL_SRCALPHA & flag ? AMASK24 : 0;
        break;
    case 16:
        rmask = RMASK16;
        gmask = GMASK16;
        bmask = BMASK16;
        amask = SDL_SRCALPHA & flag ? AMASK16 : 0;
        break;
    default:
        break;
    }

    ret->_data = SDL_CreateRGBSurface(flag, w, h, depth, rmask, gmask, bmask, amask);
    if (!ret->_data) {
        GK_WARNING("Empty surface, error:%s\n", SDL_GetError());
    }

    ret->_cx = 0;
    ret->_cy = 0;
    ret->_useAlpha = GKFALSE;

    return (ret);
}

GKSurface *GKSurface_Duplicate(GKSurface *src)
{
    guint32 origflags;

    GKSurface *dst = NULL;
    GK_NEW(dst, GKSurface);

    dst->_data = SDL_CreateRGBSurface(src->_data->flags,
                                      src->_data->w,
                                      src->_data->h,
                                      src->_data->format->BitsPerPixel,
                                      src->_data->format->Rmask,
                                      src->_data->format->Gmask,
                                      src->_data->format->Bmask,
                                      src->_data->format->Amask);
    origflags = src->_data->flags;
    src->_data->flags &= !SDL_SRCALPHA;
    SDL_BlitSurface(src->_data, NULL, dst->_data, NULL);
    src->_data->flags = origflags;

    dst->_cx = src->_cx;
    dst->_cy = src->_cy;
    dst->_useAlpha = src->_useAlpha;

    return (dst);
}

void GKSurface_Delete(GKSurface *s)
{
    SDL_FreeSurface(s->_data);
    GK_DELETE(s);
}

void GKSurface_Blit(GKSurface *src, GKSurface *dst)
{
    SDL_Rect dst_rect;
    dst_rect.x = src->_cx - src->_data->w / 2;
    dst_rect.y = src->_cy - src->_data->h / 2;

    SDL_BlitSurface(src->_data, NULL, dst->_data, &dst_rect);
}

void GKSurface_BlitXY(GKSurface *src, GKSurface *dst, gint16 ox, gint16 oy)
{
    SDL_Rect dst_rect;
    dst_rect.x = ox - src->_data->w / 2;
    dst_rect.y = oy - src->_data->h / 2;

    SDL_BlitSurface(src->_data, NULL, dst->_data, &dst_rect);
}

void GKSurface_BlitRect(GKSurface *src, GKSurface *dst, gint16 x, gint16 y, guint16 w, guint16 h)
{
    SDL_Rect src_rect;
    SDL_Rect dst_rect;

    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = w;
    src_rect.h = h;

    dst_rect.x = src->_cx - w / 2;
    dst_rect.y = src->_cy - h / 2;

    SDL_BlitSurface(src->_data, &src_rect, dst->_data, &dst_rect);
}

gbool GKSurface_CheckPixel(GKSurface *s, gint16 x, gint16 y)
{
    int bpp = s->_data->format->BytesPerPixel;
    guint8 *p = (guint8*)s->_data->pixels + y * s->_data->pitch + x * bpp;
    guint32 pixel_color;
    guint8 r, g, b, a;

    GK_LOCKSURFACE(s->_data);

    switch (bpp) {
    case (1):
        pixel_color = *p;
        break;
    case (2):
        pixel_color = *(guint16*)p;
        break;
    case (3):
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            pixel_color =  p[0] << 16 | p[1] << 8 | p[2];
        }
        else {
            pixel_color = p[0] | p[1] << 8 | p[2] << 16;
        }
    case (4):
        pixel_color = *(guint32*)p;
        break;
    }

    SDL_GetRGBA(pixel_color, s->_data->format, &r, &g, &b, &a);
    GK_UNLOCKSURFACE(s->_data);

    if (s->_useAlpha) {
        return (a > __GKSurface_Default_CollisionColor_LowerBound_);
    } else {
        return (GKTRUE);
    }
}

gbool GKSurface_BoxCollide(GKSurface *s1, GKSurface *s2)
{
    gint16 x1 = s1->_cx - s1->_data->w / 2;
    gint16 x2 = s2->_cx - s2->_data->w / 2;
    gint16 y1 = s1->_cy - s1->_data->h / 2;
    gint16 y2 = s2->_cy - s2->_data->h / 2;

    rect r1 = {x1, y1, s1->_data->w, s1->_data->h};
    rect r2 = {x2, y2, s2->_data->w, s2->_data->h};

    return (rect_collide(r1, r2));
}

gbool GKSurface_Collide(GKSurface *s1, GKSurface *s2)
{
    int x, y;
    rect collisionRect = rect_intersect(GKSurface_GetBounds(s1), GKSurface_GetBounds(s2));
    rect ms1 = rect_map(GKSurface_GetBounds(s1), collisionRect);
    rect ms2 = rect_map(GKSurface_GetBounds(s2), collisionRect);

    if(collisionRect.w == 0 && collisionRect.h == 0)
        return (GKFALSE);


    for(y = 0; y <= ms1.h; y++) {
        for(x = 0; x <= ms2.w; x++) {
            if(GKSurface_CheckPixel(s1, ms1.x + x, ms1.y + y) && GKSurface_CheckPixel(s2, ms2.x + x, ms2.y + y)) {
                return (GKTRUE);
            }
        }
    }

    return (GKFALSE);
}

void GKSurface_UseAlpha(GKSurface *s)
{
    // TODO:
    GK_UNUSED_PARAM(s);
}

void GKSurface_IgnoreAlpha(GKSurface *s)
{
    // TODO:
    GK_UNUSED_PARAM(s);
}

guint32 GKSurface_MapRGBA(GKSurface *s, guint8 r, guint8 g, guint8 b, guint8 a)
{
    if (SDL_SRCALPHA & s->_data->flags) {
        return (SDL_MapRGBA(s->_data->format, r, g, b, a));
    } else {
        return (SDL_MapRGB(s->_data->format, r, g, b));
    }
}

int GKSurface_GetDefaultDepth(void)
{
    return (__GKSurface_Default_Depth__);
}

void GKSurface_SetDefaultDepth(guint8 depth)
{
    switch (depth) {
    case 8:
    case 16:
    case 24:
    case 32:
        __GKSurface_Default_Depth__ = depth;
        break;
    default:
        GK_WARNING("%s\n", "Default depth must be (8 * N)");
        break;
    }
}

void GKSurface_DrawPixel(GKSurface *s, gint16 x, gint16 y, guint32 color)
{
    guint8 *buf8 = NULL;
    guint16 *buf16 = NULL;
    guint32 *buf32 = NULL;

    if (x < 0 || y < 0)
        return;

    if (x >= s->_data->w || y >= s->_data->h)
        return;

    switch (s->_data->format->BitsPerPixel) {
    case 8:
        buf8 = (guint8*)s->_data->pixels + GKSurface_XY2Index(s, x, y);
        *buf8 = (guint8)color;
        break;
    case 16:
        buf16 = (guint16*)s->_data->pixels + GKSurface_XY2Index(s, x, y);
        *buf16 = (guint16)color;
        break;
    default:
        buf32 = (Uint32*)s->_data->pixels + GKSurface_XY2Index(s, x, y);
        *buf32 = color;
        break;
    }
}

void GKSurface_FillRect(GKSurface *s, rect *r, guint32 color)
{
    GK_LOCKSURFACE(s->_data);
    SDL_FillRect(s->_data, (SDL_Rect*)r, color);
    GK_UNLOCKSURFACE(s->_data);
}

void GKSurface_SetPosition(GKSurface *s, gint16 x, gint16 y)
{
    s->_cx = x;
    s->_cy = y;
}

void GKSurface_Set(GKSurface *s, guint16 w, guint16 h, guint8 depth, guint32 flag)
{
    if (s) {
        GKSurface_Delete(s);
    }

    s = GKSurface_NewEmptySurface(w, h, depth, flag);
    GKSurface_LoadPalette(s);
}

void GKSurface_SetAlpha(GKSurface *s, guint8 alpha)
{
    //    int x, y;
    //    SDL_Surface *ret = GKSurface_Duplicate(s)->_data;
    //    GKPixel *pi;

    //    GKLOCK(ret);
    //    for (y = 0; y < ret->h; y++) {
    //        for (x = 0; x < ret->w; x++) {
    //            pi = GKGFX_GetPixel(ret, x, y);
    //            pi->a = pi->a * alpha / 256;
    //            GKGFX_DrawPixel(ret, x, y, GKGFX_MakeColor(ret, pi->r, pi->g, pi->b, pi->a));
    //            GKPixelInfo_Free(pi);
    //        }
    //    }
    //    GKUNLOCK(ret);
    //    return ret;


    if (!s->_data) {
        GK_WARNING("%s\n", "No surface data.");
    }
    SDL_SetAlpha(s->_data, SDL_SRCALPHA, alpha);
}

void GKSurface_SetColorkey(GKSurface *s, guint8 r, guint8 g, guint8 b)
{
    if (s->_useAlpha) {
        GK_WARNING("%s\n", "Cannot set colorkey when using alpha.");
    } else {
        SDL_SetColorKey(s->_data, SDL_SRCCOLORKEY, SDL_MapRGB(s->_data->format, r, g, b));
    }
}

void GKSurface_SetClipRect(GKSurface *s, gint16 x, gint16 y, guint16 w, guint16 h)
{
    s->_data->clip_rect.x = x;
    s->_data->clip_rect.y = y;
    s->_data->clip_rect.w = w;
    s->_data->clip_rect.h = h;
}

void GKSurface_Fill(GKSurface *s, guint32 color)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = s->_data->w;
    rect.h = s->_data->h;

    SDL_FillRect(s->_data, &rect, color);

}

void GKSurface_LoadPalette(GKSurface *s)
{
    assert(s);

    if (s->_data && (s->_data->format->BitsPerPixel == 8)) {
        const SDL_Palette *pal = GKPalette_GetInstance()->_palette;
        if (pal) {
            SDL_SetPalette(s->_data, SDL_LOGPAL | SDL_PHYSPAL, pal->colors, 0, pal->ncolors);
        }
    }
}

GKPixel *GKSurface_GetPixel(GKSurface *s, gint16 x, gint16 y)
{
    GKPixel *pix = NULL;
    int bpp = s->_data->format->BitsPerPixel;
    guint8 *p = (guint8*)s->_data->pixels + y * s->_data->pitch + x * bpp;
    guint32 pixel_color;

    switch (bpp) {
    case (1):
        pixel_color = *p;
        break;
    case (2):
        pixel_color = *(guint16*)p;
        break;
    case (3):
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            pixel_color = p[0] << 16 | p[1] << 8 | p[2];
        } else {
            pixel_color = p[0] | p[1] << 8 | p[2] << 16;
        }
        break;
    case (4):
        pixel_color = *(guint32*)p;
        break;
    }

    GK_NEW(pix, GKPixel);
    SDL_GetRGBA(pixel_color, s->_data->format, &pix->r, &pix->g, &pix->b, &pix->a);
    return (pix);
}

gint32 GKSurface_GetWidth(GKSurface *s)
{
    return (s->_data->w);
}

gint32 GKSurface_GetHeight(GKSurface *s)
{
    return (s->_data->h);
}

rect GKSurface_GetBounds(GKSurface *s)
{
    rect bounds;
    bounds.x = s->_cx - s->_data->w / 2;
    bounds.y = s->_cy - s->_data->h / 2;
    bounds.w = s->_data->w;
    bounds.h = s->_data->h;

    return (bounds);
}

guint32 GKSurface_GetColorkey(GKSurface *s)
{
    assert(s);
    return (SDL_MapRGBA(s->_data->format, 0xFF, 0xFF, 0xFF, 0));
}
