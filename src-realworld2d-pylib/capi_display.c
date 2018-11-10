#include <Python.h>
#include <SDL/SDL.h>

#include "globaldefs.h"
#include "scriptengine.h"

static SDL_Surface *_display = NULL;

void _blitxy(struct SDL_Surface *src, struct SDL_Surface *dst, int ox, int oy) {
    if (NULL == src || NULL == dst) {
        GK_WARNING("Src surface or dest surface is NULL.");
        return;
    }

    SDL_Rect dst_rect;
    dst_rect.x = ox;
    dst_rect.y = oy;
    dst_rect.w = src->w;
    dst_rect.h = src->h;

    SDL_BlitSurface(src, NULL, dst, &dst_rect);
}

PyObject *
capi_display_init(PyObject *self, PyObject *args) {
    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    GK_MSG("openning display window...");
    if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        GK_BAILOUT("Initialize graphics environment failed.");
        Py_RETURN_FALSE;
    }

    // singleton method
    if (NULL == _display) {
        _display = SDL_GetVideoSurface();
    }
    Py_RETURN_TRUE;
}


PyObject*
capi_display_setvediomode(PyObject* self, PyObject* args) {
    gint32 w = 0;
    gint32 h = 0;
    gint32 full_screen = GKFALSE;

    GK_UNUSED_PARAM(self);

    if (_display && _display->w && _display->h) {
        GK_MSG("Display already exists.");
        Py_RETURN_TRUE;
    }

    if (!PyArg_ParseTuple(args, "iii", &w, &h, &full_screen)) {
        GK_MSG("Python arg input error.");
        Py_RETURN_FALSE;
    }

    guint32 video_flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL;
    if (full_screen || (_display && (_display->flags & SDL_FULLSCREEN))) {
        video_flags = video_flags | SDL_FULLSCREEN;
    }

    _display = SDL_SetVideoMode(w, h, 32, video_flags);

    if (!_display) {
        _display = SDL_SetVideoMode(640, 480, 32, video_flags);
        GK_BAILOUT("%s", SDL_GetError());
        Py_RETURN_FALSE;
    }
    Py_RETURN_TRUE;
}

PyObject*
capi_display_setcaption(PyObject* self, PyObject* args) {
    char *caption = NULL;

    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    if (!PyArg_ParseTuple(args, "s", &caption)) {
        GK_WARNING("Python arg input error.");
        Py_RETURN_FALSE;
    }

    if (strlen(caption)) {
        SDL_WM_SetCaption(caption, NULL);
        Py_RETURN_TRUE;
    } else {
        GK_WARNING("Invalid input");
        Py_RETURN_FALSE;
    }
}

PyObject*
capi_display_close(PyObject* self, PyObject* args) {
    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    SDL_VideoQuit();
    Py_RETURN_NONE;
}

PyObject*
capi_display_blitsurface(PyObject* self, PyObject* args) {
    int offset_x, offset_y;
    gint32 key = 0;

    GK_UNUSED_PARAM(self);

    if (!PyArg_ParseTuple(args, "Iii", &key, &offset_x, &offset_y)) {
        GK_WARNING("Python arg input error.");
        Py_RETURN_FALSE;
    }

    SDL_Surface *surface = assets_getsurface(key);
    if (NULL == surface) {
        GK_WARNING("surface not found");
        Py_RETURN_FALSE;
    }

    printf("Find surface data at %p.\n", surface);
    _blitxy(surface, _display, offset_x, offset_y);

    Py_RETURN_TRUE;
}

PyObject *
capi_display_flip(PyObject *self, PyObject *args) {
    SDL_Flip(_display);
    Py_RETURN_NONE;
}

static PyMethodDef capi_display_methods[] = {
    { "init", capi_display_init, METH_NOARGS, "Initialize a display." },
    { "setvideomode", capi_display_setvediomode, METH_VARARGS, "Set display video-mode." },
    { "setcaption", capi_display_setcaption, METH_VARARGS, "Set display caption." },
    { "close", capi_display_close, METH_NOARGS, "Clear all timers." },
    { "blit_surface", capi_display_blitsurface, METH_VARARGS, "Clear all timers." },
    { "flip", capi_display_flip, METH_NOARGS, "Flip the display." },
    { NULL, NULL, 0, NULL }
};

void
capi_load_display(void) {
    PyObject* m;
    m = Py_InitModule("display", capi_display_methods);
}
