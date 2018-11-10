#include <Python.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//#include "hashtable.h"
//#include "graphicsutils.h"
//#include "surface.h"
//#include "scriptengine.h"

//static const guint32 INIT_ICONCACHE_SIZE = 100;

//static const char * _module_doc = \
//        "\nThis module is used for gkgraphics generation. \n" \
//        "Usage: \n";

//PyObject *
//capi_assets_init(PyObject *self, PyObject *args) {
//    GK_UNUSED_PARAM(self);
//    GK_UNUSED_PARAM(args);

//    if (!_assets.initialized) {
//        _assets.surface_cache = hashtable_new(INIT_ICONCACHE_SIZE);
//        _assets.initialized = GKTRUE;
//    }

//    Py_RETURN_NONE;
//}

//PyObject *
//capi_assets_finalize(PyObject *self, PyObject *args) {
//    if (_assets.initialized) {
//        _assets.initialized = GKFALSE;
//        hashtable_del(_assets.surface_cache, SDL_FreeSurface);
//    }

//    Py_RETURN_NONE;
//}

//int assets_loadsurface(const char *file_name) {
//    SDL_Surface *sur = graphics_loadsurface(file_name, 0);
//    return hashtable_insert(_assets.surface_cache, sur);
//}

//SDL_Surface *assets_getsurface(gint32 key) {
//    return (SDL_Surface*)hashtable_search(_assets.surface_cache, key);
//}

//PyObject *
//capi_assets_loadsurface(PyObject *self, PyObject *args) {
//    GK_UNUSED_PARAM(self);

//    int key = 0;
//    char *file_name = NULL;

//    if (!PyArg_ParseTuple(args, "s", &file_name)) {
//        GK_MSG("Python arg input error.");
//        return NULL;
//    }

//    SDL_Surface *sur = graphics_loadsurface(file_name, 0);
////    scriptengine_runstr("print os.getcwd()");
////    surface *sur = surface_new_fromfile(file_name, 0);
////    printf("%p", sur);
//    key = hashtable_insert(_assets.surface_cache, sur);

//    return Py_BuildValue("i", key);
//}

//PyObject *
//capi_assets_delsurface(PyObject *self, PyObject *args) {
//    GK_UNUSED_PARAM(self);

//    int key = 0;

//    if (!PyArg_ParseTuple(args, "i", &key)) {
//        GK_MSG("Python arg input error.");
//        Py_RETURN_FALSE;
//    }

//    SDL_Surface *surface = hashtable_search(_assets.surface_cache, key);
//    if (NULL == surface) {
//        GK_WARNING("Surface not found.");
//        Py_RETURN_FALSE;
//    }

//    printf("Free surface at 0x%p.\n", surface);
//    SDL_FreeSurface(surface);

//    hashtable_remove(_assets.surface_cache, key, SDL_FreeSurface);
//    Py_RETURN_TRUE;
//}

//static PyMethodDef
//capi_assets_methods[] = {
//    { "init", capi_assets_init, METH_NOARGS, "Initialize assets." },
//    { "load_surface", capi_assets_loadsurface, METH_VARARGS, "Load a surface from file." },
//    { "del_surface", capi_assets_delsurface, METH_VARARGS, "Initialize gkdisplay." },
//    { NULL, NULL, 0, NULL }
//};

//void
//capi_load_assets(void) {
//    PyObject* m= Py_InitModule3("assets", capi_assets_methods, _module_doc);
//    GK_UNUSED_PARAM(m);
//}
