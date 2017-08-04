#include <Python.h>

#include "scriptengine.h"
#include "globaldefs.h"
#include "hashtable.h"
#include "timer.h"

static gbool initialized = GKFALSE;
static gint32 timerht_size = 50;
static hashtable *timerht = NULL;

PyObject*
capi_timer_new(PyObject* self, PyObject* args) {
    gint32 timer_id = 0;

    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    if (!initialized) {
        timerht = hashtable_new(timerht_size);
        initialized = GKTRUE;
    }

    timer *t = timer_new();
    timer_id = hashtable_insert(timerht, t);


    return Py_BuildValue("i", timer_id);
}

PyObject*
capi_timer_remove(PyObject* self, PyObject* args) {
    gint32 timer_id = 0;
    gint32 result = 0;

    GK_UNUSED_PARAM(self);

    if (!PyArg_ParseTuple(args, "i", &timer_id)) {
        return NULL;
    }

    result = hashtable_remove(timerht, timer_id, timer_del);

    return PyBool_FromLong(result);
}

PyObject*
capi_timer_clearall(PyObject* self, PyObject* args) {
    gint32 result = GKFALSE;

    GK_UNUSED_PARAM(self);

    if (initialized) {
        hashtable_del(timerht, timer_del);
        result = GKTRUE;
        initialized = GKFALSE;
    }

    return PyBool_FromLong(result);
}

static PyMethodDef capi_timer_methods[] = {
    { "new", capi_timer_new, METH_NOARGS, "Initialize random generator." },
    { "remove", capi_timer_remove, METH_VARARGS, "Get a random integer number." },
    { "clearall", capi_timer_clearall, METH_NOARGS, "Get a random integer number." },
    { NULL, NULL, 0, NULL }
};

void
capi_load_timer(void) {
    PyObject* m;
    m = Py_InitModule("timer", capi_timer_methods);
}
