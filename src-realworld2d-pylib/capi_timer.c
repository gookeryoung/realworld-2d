#include <Python.h>

#include "globaldefs.h"
#include "timer.h"

PyObject*
capi_timer_new(PyObject* self, PyObject* args) {
    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    srand((unsigned int)time(NULL));
    Py_RETURN_NONE;
}

PyObject*
py_rand_get(PyObject* self, PyObject* args) {
    unsigned int min;
    unsigned int max;
    unsigned int result;

    GK_UNUSED_PARAM(self);

    if (!PyArg_ParseTuple(args, "II", &min, &max)) {
        return NULL;
    }
    result = max ? min + (rand() % (max - min + 1)) : rand() % (min + 1);

    return Py_BuildValue("I", result);
}

static PyMethodDef py_rand_methods[] = {
    { "init", capi_timer_new, METH_NOARGS, "Initialize random generator." },
    { "get", py_rand_get, METH_VARARGS, "Get a random integer number." },
    { NULL, NULL, 0, NULL }
};

void
engine_load_rand(void) {
    PyObject* m;
    m = Py_InitModule("rand", py_rand_methods);
}
