#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display* display;
    Window window;
    XEvent event;
    int screen;

    // Opens connection to X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    // Gets default display screen
    screen = DefaultScreen(display);

    // Creates a simple window
    window = XCreateSimpleWindow(
        display, RootWindow(display, screen), 10, 10, 800, 600, 1,
        BlackPixel(display, screen), WhitePixel(display, screen)
    );

    // Defines the used examples
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Show the window
    XMapWindow(display, window);

    // Event loop
    while (1) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, screen), 50, 50, "Hello, X11!", 10);
        }

        if (event.type == KeyPress) {
            break;
        }
    }

    XCloseDisplay(display);
    
    return 0;
}