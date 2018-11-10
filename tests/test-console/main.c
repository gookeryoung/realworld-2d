#include <stdio.h>
#include <SDL/SDL.h>
#include "globaldefs.h"
#include "scriptengine.h"
#include "screen.h"
#include "surface.h"
#include "event.h"


#define BUFFER_SIZE 256

#undef main
int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];

    GK_UNUSED_PARAM(argc);
    GK_UNUSED_PARAM(argv);

    scriptengine_init();


    scriptengine_runfile("example01_display.py");
//    scriptengine_runstr("main_func()");

//    while (1) {
//        printf(">>>");
//        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
//            scriptengine_runstr(buffer);
//        } else {
//            break;
//        }
//    }

//    screen *screen = screen_get();
//    screen_setvideomode(800, 600, 0);
    scriptengine_runstr("main_func()");

//    surface *sur = surface_new_fromfile("background.png", 0);

    event *event = event_get();
    while (event_handle_events(event)) {
//        scriptengine_runstr("on_render()");
//        surface_blitxy(sur, screen->data, 0, 0);
        scriptengine_runstr("on_render()");
//        screen_flip();
    }

//    scriptengine_runstr("on_exit()");

    scriptengine_exit();

    return 0;
}
