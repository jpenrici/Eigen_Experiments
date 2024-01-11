#include "functions.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>
#include <vector>


void capture(std::vector<uint8_t> &pixels, int &width, int &height, int &bitsPerPixel);

auto main() -> int
{
    int width{0}, height{0}, bpp{0};
    std::vector<std::uint8_t> pixels;

    capture(pixels, width, height, bpp);
    if (width && height) {
        width *= (bpp > 24 ? 4 : 3);

        Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic> mat;
        vec2matrix(mat, pixels, width, height);
        //save("scrrenshot.csv", toStr(mat), false);
        saveCSV(mat, "scrrenshot.csv");
    }

    return 0;
}

void capture(std::vector<uint8_t> &pixels, int &width, int &height, int &bitsPerPixel)
{
    Display *display = XOpenDisplay(nullptr);   // Open a connection to the X server.
    Window root = DefaultRootWindow(display);   // Root window for the default screen.

    XWindowAttributes attributes = {0};         // Struct with Windows attributes.
    XGetWindowAttributes(display, root, &attributes);

    width = attributes.width;
    height = attributes.height;

    XImage *img = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);  // Image object.
    bitsPerPixel = img->bits_per_pixel;
    pixels.resize(width * height * 4);

    memcpy(&pixels[0], img->data, pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
}
