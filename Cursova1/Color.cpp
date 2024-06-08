#include "Color.h"

Color::Color(int r, int g, int b)
    : r(r), g(g), b(b) {}

int Color::getRed() const {
    return r;
}

int Color::getGreen() const {
    return g;
}

int Color::getBlue() const {
    return b;
}
