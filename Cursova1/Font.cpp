#include "Font.h"

Font::Font(const std::wstring& name, int size)
    : name(name), size(size) {}

const std::wstring& Font::getName() const {
    return name;
}

int Font::getSize() const {
    return size;
}
