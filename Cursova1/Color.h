#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    Color(int r, int g, int b);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

private:
    int r, g, b;
};

#endif // COLOR_H
