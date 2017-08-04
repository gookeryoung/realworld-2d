#include <stdio.h>
#include "scriptengine.h"

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];

    scriptengine_init();

    while (1) {
        printf(">>>");
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            scriptengine_runstr(buffer);
        }
    }


    scriptengine_exit();

    return 0;
}
