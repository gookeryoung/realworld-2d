#include <Python.h>

#include "globaldefs.h"
#include "scriptengine.h"
#include "hashtable.h"
#include "event.h"

event *_event = NULL;

PyObject*
capi_event_handle_events(PyObject* self, PyObject* args) {
    GK_UNUSED_PARAM(self);
    GK_UNUSED_PARAM(args);

    _event = event_get();

    return PyBool_FromLong(event_handle_events(_event));
}
static PyMethodDef capi_gameevent_methods[] = {
    { "handle_events", capi_event_handle_events, METH_NOARGS, "Handle events." },
    { NULL, NULL, 0, NULL }
};

void
capi_load_gameevent(void) {
    PyObject* m;
    m = Py_InitModule("game_event", capi_gameevent_methods);
}
