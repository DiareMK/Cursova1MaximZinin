#include "DisplayManager.h"

DisplayManager::DisplayManager(Screen& screen)
    : screen(screen) {}

void DisplayManager::displayMessage(const Message& message, DisplayEffect& effect, int speed) {
    effect.applyEffect(message, speed);
}
