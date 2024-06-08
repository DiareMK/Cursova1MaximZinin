#ifndef FONT_H
#define FONT_H

#include <string>

class Font {
public:
    Font(const std::wstring& name, int size);
        

    const std::wstring& getName() const;
    int getSize() const;

private:
    std::wstring name;
    int size;
};

#endif // FONT_H
