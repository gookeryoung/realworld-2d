#include <Python.h>

#include "scriptengine.h"
#include "globaldefs.h"
#include "hashtable.h"
#include "timer.h"

static gint32 TIMER_HASHTABLE_SIZE = 20;

static struct _timer_container {
    gbool initialized;
    hashtable *timers;
} container = {
    GKFALSE,
    NULL
};

PyObject*
capi_timer_new(PyObject* self, PyObject* args) {
    gint32 timer_id = 0;

    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    if (!container.initialized) {
        container.timers = hashtable_new(TIMER_HASHTABLE_SIZE);
        container.initialized = GKTRUE;
    }

    timer *t = timer_new();
    timer_id = hashtable_insert(container.timers, t);

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

    result = hashtable_remove(container.timers, timer_id, timer_del);

    return PyBool_FromLong(result);
}

PyObject*
capi_timer_clearall(PyObject* self, PyObject* args) {
    gint32 result = GKFALSE;

    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    if (container.initialized) {
        hashtable_del(container.timers, timer_del);
        result = GKTRUE;
        container.initialized = GKFALSE;
    }

    return PyBool_FromLong(result);
}

static PyMethodDef capi_timer_methods[] = {
    { "new", capi_timer_new, METH_NOARGS, "Create a new timer, returns the id of it." },
    { "remove", capi_timer_remove, METH_VARARGS, "Remove a timer." },
    { "clearall", capi_timer_clearall, METH_NOARGS, "Clear all timers." },
    { NULL, NULL, 0, NULL }
};

void
capi_load_timer(void) {
    PyObject* m;
    m = Py_InitModule("timer", capi_timer_methods);
}
