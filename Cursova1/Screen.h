#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
    Screen(int width, int height);

    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
};

#endif // SCREEN_H
