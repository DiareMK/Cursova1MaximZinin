#include "Message.h"

Message::Message(const std::wstring& text, const Font& font, const Color& color)
    : text(text), font(font), color(color) {}

const std::wstring& Message::getText() const {
    return text;
}

const Font& Message::getFont() const {
    return font;
}

const Color& Message::getColor() const {
    return color;
}

void Message::setFont(const Font& newFont) {
    font = newFont;
}

void Message::setColor(const Color& newColor) {
    color = newColor;
}
