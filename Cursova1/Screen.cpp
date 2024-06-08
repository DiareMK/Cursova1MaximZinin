#include "Screen.h"

Screen::Screen(int width, int height)
    : width(width), height(height) {}

int Screen::getWidth() const {
    return width;
}

int Screen::getHeight() const {
    return height;
}
