// gcc -s -o main src/*.c -lkernel32 -lopengl32 -lgdi32 -luser32 -nostdlib -mwindows --entry=_start

#include "window.h"
#include <GL/gl.h>

int start()
{
    Window *window = window_init(320, 240, "OpenGL Window");

    if (!window) {
        return 0;
    }

    // Enable vertical synchronization
    swap_interval(1);

    while (window_isopen(window))
    {
        poll_events();
        glClear(GL_COLOR_BUFFER_BIT);
        window_swap_buffers(window);
    }
    
    window_destroy(window);
    ExitProcess(0);
}
