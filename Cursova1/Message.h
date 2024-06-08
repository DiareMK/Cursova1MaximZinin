#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "Font.h"
#include "Color.h"

class Message {
public:
    Message(const std::wstring& text, const Font& font, const Color& color);

    const std::wstring& getText() const;
    const Font& getFont() const;
    const Color& getColor() const;

    void setFont(const Font& newFont);
    void setColor(const Color& newColor);

private:
    std::wstring text;
    Font font;
    Color color;
};

#endif // MESSAGE_H
