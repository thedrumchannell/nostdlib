#include "window.h"
#include <GL/gl.h>

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window *window = window = GetProp(hwnd, "NGEWindow");

    switch(msg)
    {
        case WM_CLOSE:
            window->isOpen = 0;
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
    return 0;
}

Window *window_init(int width, int height, const char *title)
{
    Window *window = (Window*) malloc(sizeof(Window));
    
    if (!window) {
        return NULL;
    }

    window->width = width;
    window->height = height;
    window->title = title;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    char className[] = "NGEWindowClass";

    // Setup and register the window class
    window->wc.style = CS_HREDRAW | CS_VREDRAW;
    window->wc.lpfnWndProc = window_proc;
    window->wc.cbClsExtra = 0;
    window->wc.cbWndExtra = 0;
    window->wc.hIcon = NULL;
    window->wc.hInstance = hInstance;
    window->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    window->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window->wc.lpszMenuName  = NULL;
    window->wc.lpszClassName = className;
    
    RegisterClass(&window->wc);

    // Create the application window
    window->hwnd = CreateWindow(
        className,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, 
        NULL,
        hInstance,
        NULL
    );

    if (!window->hwnd) {
        return NULL;
    }
    
    // Set property for window procedure
    SetProp(window->hwnd, "NGEWindow", window);

    // Get the device context
    window->hdc = GetDC(window->hwnd);

    // Create the pixel format descriptor
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;

    // Set the pixel format
    int pf = ChoosePixelFormat(window->hdc, &pfd);
    SetPixelFormat(window->hdc, pf, &pfd);
    
    // Create the rendering context for this window
    window->hglrc = wglCreateContext(window->hdc);

    // Make the context current
    wglMakeCurrent(window->hdc, window->hglrc);

    // Initialize OpenGL
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glClearColor(0.f, 0.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);

    // Show the window now that everything is setup
    ShowWindow(window->hwnd, SW_SHOW);

    window->isOpen = 1;

    return window;
}

int window_isopen(Window *window)
{
    return window->isOpen;
}

void window_swap_buffers(Window *window)
{
    SwapBuffers(window->hdc);
}

void window_destroy(Window *window)
{
    DestroyWindow(window->hwnd);
    free(window);
}

void poll_events()
{
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void swap_interval(int interval)
{
    typedef int (WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int interval);
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    wglSwapIntervalEXT(interval);
}
