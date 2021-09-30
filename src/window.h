#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

typedef struct Window
{
    int width;
    int height;
    const char *title;
    int isOpen;
    HWND hwnd;
    WNDCLASS wc;
    HDC hdc;
    HGLRC hglrc;
} Window;

Window *window_init(int width, int height, const char *title);
LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int window_isopen(Window *window);
void window_swap_buffers(Window *window);
void window_destroy(Window *window);
void poll_events();
void swap_interval(int interval);

#endif
