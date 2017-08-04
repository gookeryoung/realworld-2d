#include <Python.h>

void
scriptengine_init() {
    Py_Initialize();

    /* change app directory to 'scripts' folder to read python scripts */
    PyRun_SimpleString("import os");
    PyRun_SimpleString("os.chdir('./scripts')");
    PyRun_SimpleString("print os.getcwd()");

    /* add 'scripts' folder to python environment */
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
}

void
scriptengine_exit() {
    Py_Finalize();
}

int
scriptengine_runstr(const char *str) {
    if (NULL == str) {
        // TODO: error handling
        return 0;
    }

    PyRun_SimpleString(str);

    return 1;
}

int
scriptengine_runfile(const char *file_name)
{
    FILE *fp = NULL;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("failed open file: [%s]\n", file_name);
        return 0;
    } else {
        printf("successfully open file: [%s]\n", file_name);
        PyRun_SimpleFile(fp, file_name);
    }

    return 1;
}
