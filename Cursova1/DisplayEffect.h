#ifndef DISPLAYEFFECT_H
#define DISPLAYEFFECT_H

#include "Message.h"

class DisplayEffect {
public:
    virtual void applyEffect(const Message& message, int speed) = 0;
};

class TickerEffect : public DisplayEffect {
public:
    void applyEffect(const Message& message, int speed) override;
};

class BlinkEffect : public DisplayEffect {
public:
    void applyEffect(const Message& message, int speed) override;
};

#endif // DISPLAYEFFECT_H
