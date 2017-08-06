#include <stdio.h>
#include "globaldefs.h"
#include "scriptengine.h"

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];

    GK_UNUSED_PARAM(argc);
    GK_UNUSED_PARAM(argv);

    scriptengine_init();

    while (1) {
        printf(">>>");
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            scriptengine_runstr(buffer);
        } else {
            break;
        }
    }

    scriptengine_exit();

    return 0;
}
