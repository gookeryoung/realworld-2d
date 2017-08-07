#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphics.h"
#include "palette.h"
#include "surface.h"

static guint8 _default_depth = 16;
static guint8 _default_collision_color_lowerbound = 200;

pixel *
pixel_new(guint8 r, guint8 g, guint8 b, guint8 a) {
    pixel *ret = NULL;
    GK_NEW(ret, pixel);

    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;

    return (ret);
}

void
pixel_del(pixel *p) {
    GK_DELETE(p);
}

surface *
surface_new(void) {
    surface *ret = NULL;
    GK_NEW(ret, surface);

    ret->data = NULL;
    ret->use_alpha = GKFALSE;
    ret->cx = 0;
    ret->cy = 0;

    return (ret);
}

surface *
surface_new_fromfile(const char *file_name, gbool use_alpha) {
    SDL_Surface *loaded = NULL;
    surface *ret = NULL;
    GK_NEW(ret, surface);

    ret->use_alpha = use_alpha;

    loaded = IMG_Load(file_name);
    if (loaded != NULL) {
        ret->data = use_alpha ? SDL_DisplayFormatAlpha(loaded) : SDL_DisplayFormat(loaded);
        SDL_FreeSurface(loaded);
    } else {
        GK_BAILOUT("Failed loading surface [%s]: [%s]", file_name, IMG_GetError());
    }

    ret->cx = ret->data->w / 2;
    ret->cy = ret->data->h / 2;

    return (ret);
}

surface *
surface_new_empty(guint16 w, guint16 h, guint8 depth, guint32 flag) {
    guint32 rmask = 0;
    guint32 gmask = 0;
    guint32 bmask = 0;
    guint32 amask = 0;

    surface *ret = NULL;
    GK_NEW(ret, surface);

    switch (depth) {
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

    ret->data = SDL_CreateRGBSurface(flag, w, h, depth, rmask, gmask, bmask, amask);
    if (!ret->data) {
        GK_WARNING("Empty surface, error:%s\n", SDL_GetError());
    }

    ret->cx = 0;
    ret->cy = 0;
    ret->use_alpha = GKFALSE;

    return (ret);
}

surface *
surface_copy(surface *src) {
    guint32 origflags = 0;
    surface *dst = NULL;
    GK_NEW(dst, surface);

    dst->data = SDL_CreateRGBSurface(src->data->flags,
                                      src->data->w,
                                      src->data->h,
                                      src->data->format->BitsPerPixel,
                                      src->data->format->Rmask,
                                      src->data->format->Gmask,
                                      src->data->format->Bmask,
                                      src->data->format->Amask);
    origflags = src->data->flags;
    src->data->flags &= !SDL_SRCALPHA;
    SDL_BlitSurface(src->data, NULL, dst->data, NULL);
    src->data->flags = origflags;

    dst->cx = src->cx;
    dst->cy = src->cy;
    dst->use_alpha = src->use_alpha;

    return (dst);
}

void
surface_del(surface *s) {
    SDL_FreeSurface(s->data);
    GK_DELETE(s);
}

void
surface_blit(surface *src, surface *dst) {
    SDL_Rect dst_rect;
    dst_rect.x = src->cx - src->data->w / 2;
    dst_rect.y = src->cy - src->data->h / 2;

    SDL_BlitSurface(src->data, NULL, dst->data, &dst_rect);
}

void
surface_blitxy(surface *src, surface *dst, gint16 ox, gint16 oy) {
    SDL_Rect dst_rect;
    dst_rect.x = ox - src->data->w / 2;
    dst_rect.y = oy - src->data->h / 2;

    SDL_BlitSurface(src->data, NULL, dst->data, &dst_rect);
}

void
surface_blitrect(surface *src, surface *dst, gint16 x, gint16 y, guint16 w, guint16 h) {
    SDL_Rect src_rect;
    SDL_Rect dst_rect;

    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = w;
    src_rect.h = h;

    dst_rect.x = src->cx - w / 2;
    dst_rect.y = src->cy - h / 2;

    SDL_BlitSurface(src->data, &src_rect, dst->data, &dst_rect);
}

gbool
surface_checkpixel(surface *s, gint16 x, gint16 y) {
    int bpp = s->data->format->BytesPerPixel;
    guint8 *p = (guint8*)s->data->pixels + y * s->data->pitch + x * bpp;
    guint32 pixel_color;
    guint8 r, g, b, a;

    GK_LOCKSURFACE(s->data);

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

    SDL_GetRGBA(pixel_color, s->data->format, &r, &g, &b, &a);
    GK_UNLOCKSURFACE(s->data);

    if (s->use_alpha) {
        return (a > _default_collision_color_lowerbound);
    } else {
        return (GKTRUE);
    }
}

gbool
surface_collidebox(surface *s1, surface *s2) {
    gint16 x1 = s1->cx - s1->data->w / 2;
    gint16 x2 = s2->cx - s2->data->w / 2;
    gint16 y1 = s1->cy - s1->data->h / 2;
    gint16 y2 = s2->cy - s2->data->h / 2;

    rect r1 = {x1, y1, s1->data->w, s1->data->h};
    rect r2 = {x2, y2, s2->data->w, s2->data->h};

    return (rect_collide(r1, r2));
}

gbool
surface_collide(surface *s1, surface *s2) {
    int x, y;
    rect collisionRect = rect_intersect(surface_getbounds(s1), surface_getbounds(s2));
    rect ms1 = rect_map(surface_getbounds(s1), collisionRect);
    rect ms2 = rect_map(surface_getbounds(s2), collisionRect);

    if(collisionRect.w == 0 && collisionRect.h == 0)
        return (GKFALSE);

    for(y = 0; y <= ms1.h; y++) {
        for(x = 0; x <= ms2.w; x++) {
            if(surface_checkpixel(s1, ms1.x + x, ms1.y + y) && surface_checkpixel(s2, ms2.x + x, ms2.y + y)) {
                return (GKTRUE);
            }
        }
    }

    return (GKFALSE);
}

void
surface_usealpha(surface *s) {
    // TODO:
    GK_UNUSED_PARAM(s);
}

void
surface_ignorealpha(surface *s) {
    // TODO:
    GK_UNUSED_PARAM(s);
}

guint32
surface_map_rgba(surface *s, guint8 r, guint8 g, guint8 b, guint8 a) {
    if (SDL_SRCALPHA & s->data->flags) {
        return (SDL_MapRGBA(s->data->format, r, g, b, a));
    } else {
        return (SDL_MapRGB(s->data->format, r, g, b));
    }
}

guint8 surface_getdefaultdepth(void) {
    return (_default_depth);
}

void
surface_setdefaultdepth(guint8 depth) {
    switch (depth) {
    case 8:
    case 16:
    case 24:
    case 32:
        _default_depth = depth;
        break;
    default:
        GK_WARNING("%s\n", "Default depth must be (8 * N)");
        break;
    }
}

void
surface_drawpixel(surface *s, gint16 x, gint16 y, guint32 color) {
    guint8 *buf8 = NULL;
    guint16 *buf16 = NULL;
    guint32 *buf32 = NULL;

    if (x < 0 || y < 0)
        return;

    if (x >= s->data->w || y >= s->data->h)
        return;

    switch (s->data->format->BitsPerPixel) {
    case 8:
        buf8 = (guint8*)s->data->pixels + surface_xy2index(s, x, y);
        *buf8 = (guint8)color;
        break;
    case 16:
        buf16 = (guint16*)s->data->pixels + surface_xy2index(s, x, y);
        *buf16 = (guint16)color;
        break;
    default:
        buf32 = (Uint32*)s->data->pixels + surface_xy2index(s, x, y);
        *buf32 = color;
        break;
    }
}

void
surface_fillrect(surface *s, rect *r, guint32 color) {
    GK_LOCKSURFACE(s->data);
    SDL_FillRect(s->data, (SDL_Rect*)r, color);
    GK_UNLOCKSURFACE(s->data);
}

void
surface_setposition(surface *s, gint16 x, gint16 y) {
    s->cx = x;
    s->cy = y;
}

void
surface_set(surface *s, guint16 w, guint16 h, guint8 depth, guint32 flag) {
    if (s) {
        surface_del(s);
    }

    s = surface_new_empty(w, h, depth, flag);
    surface_loadpalette(s);
}

void
surface_setalpha(surface *s, guint8 alpha) {
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

    if (!s->data) {
        GK_WARNING("%s\n", "No surface data.");
    }
    SDL_SetAlpha(s->data, SDL_SRCALPHA, alpha);
}

void
surface_setcolorkey(surface *s, guint8 r, guint8 g, guint8 b) {
    if (s->use_alpha) {
        GK_WARNING("%s\n", "Cannot set colorkey when using alpha.");
    } else {
        SDL_SetColorKey(s->data, SDL_SRCCOLORKEY, SDL_MapRGB(s->data->format, r, g, b));
    }
}

void
surface_setcliprect(surface *s, gint16 x, gint16 y, guint16 w, guint16 h) {
    s->data->clip_rect.x = x;
    s->data->clip_rect.y = y;
    s->data->clip_rect.w = w;
    s->data->clip_rect.h = h;
}

void
surface_fill(surface *s, guint32 color) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = s->data->w;
    rect.h = s->data->h;

    SDL_FillRect(s->data, &rect, color);

}

void
surface_loadpalette(surface *s) {
    assert(s);

    if (s->data && (s->data->format->BitsPerPixel == 8)) {
        const SDL_Palette *pal = palette_get()->data;
        if (pal) {
            SDL_SetPalette(s->data, SDL_LOGPAL | SDL_PHYSPAL, pal->colors, 0, pal->ncolors);
        }
    }
}

pixel *
surface_getpixel(surface *s, gint16 x, gint16 y) {
    pixel *pix = NULL;
    guint8 bpp = s->data->format->BitsPerPixel;
    guint8 *p = (guint8*)s->data->pixels + y * s->data->pitch + x * bpp;
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

    GK_NEW(pix, pixel);
    SDL_GetRGBA(pixel_color, s->data->format, &pix->r, &pix->g, &pix->b, &pix->a);
    return (pix);
}

gint32
surface_getwidth(surface *s) {
    return (s->data->w);
}

gint32
surface_getheight(surface *s) {
    return (s->data->h);
}

rect
surface_getbounds(surface *s) {
    rect bounds;
    bounds.x = s->cx - s->data->w / 2;
    bounds.y = s->cy - s->data->h / 2;
    bounds.w = s->data->w;
    bounds.h = s->data->h;

    return (bounds);
}

guint32
surface_getcolorkey(surface *s) {
    GK_ASSERT(s);
    return (SDL_MapRGBA(s->data->format, 0xFF, 0xFF, 0xFF, 0));
}
