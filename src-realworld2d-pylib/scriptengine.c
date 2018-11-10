#include <Python.h>

#include "scriptengine.h"

int scriptengine_init() {
    printf("Entering python script environment...\n");
    Py_Initialize();

    int result = 0;
    /* change app directory to 'scripts' folder to read python scripts */
    result += scriptengine_runstr("import os");
    result += scriptengine_runstr("import sys");
//    result += scriptengine_runstr("sys.path.append('./')");
    result += scriptengine_runstr("os.chdir('./scripts')");
    result += scriptengine_runstr("print 'Current working directory: [', os.getcwd(), ']'");

    /* add 'scripts' folder to python environment */
    result += scriptengine_runstr("sys.path.append('./')");

    //
    capi_load_timer();
    capi_load_assets();
    capi_load_display();
    capi_load_gameevent();

    return (0 == result ? 0 : -1);
}

void
scriptengine_exit() {
    Py_Finalize();
}

int
scriptengine_runstr(const char *str) {
    if (!strlen(str)) {
        fprintf(stderr, "String is empty.\n");
        return -1;
    }

    printf("Run python code: [%s].\n", str);
    return PyRun_SimpleString(str);
}

int
scriptengine_runfile(const char *file_name)
{
    FILE *fp = NULL;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("failed open file: [%s]\n", file_name);
        return -1;
    }

    printf("successfully open file: [%s]\n", file_name);
    PyRun_SimpleFile(fp, file_name);
    return 0;
}
