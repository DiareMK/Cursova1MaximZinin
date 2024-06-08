#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Screen.h"
#include "Message.h"
#include "DisplayEffect.h"

class DisplayManager {
public:
    DisplayManager(Screen& screen);

    void displayMessage(const Message& message, DisplayEffect& effect, int speed);

private:
    Screen& screen;
};

#endif // DISPLAYMANAGER_H
