#include "DisplayEffect.h"
#include <iostream>
#include <thread>
#include <chrono>

void TickerEffect::applyEffect(const Message& message, int speed) {
    std::wstring text = message.getText();
    int width = 20;
    while (true) {
        for (size_t i = 0; i < text.length() + width; ++i) {
            std::wstring displayText;
            for (size_t j = 0; j < width; ++j) {
                size_t index = (i + j) % text.length();
                displayText += text[index];
            }
            std::wcout << L"\r" << L"\x1B[38;2;" << message.getColor().getRed() << L";" << message.getColor().getGreen() << L";" << message.getColor().getBlue()<< L"m" << displayText << L"\x1B[0m" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
    }
}

void BlinkEffect::applyEffect(const Message& message, int speed) {
    while (true) {
        std::wcout << L"\r" << L"\x1B[38;2;"
            << message.getColor().getRed()
            << L";" << message.getColor().getGreen()
            << L";" << message.getColor().getBlue()
            << L"m" << message.getText()
            << L"\x1B[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        std::wcout << L"\r" << std::wstring(message.getText().length(), L' ') << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}
