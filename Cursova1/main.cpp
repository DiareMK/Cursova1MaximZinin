#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Screen.h"
#include "Font.h"
#include "Color.h"
#include "Message.h"
#include "DisplayEffect.h"
#include "DisplayManager.h"

Color selectColor();
Font selectFont(const std::vector<std::wstring>& availableFonts);
int selectSpeed();
int selectEffect();
std::wstring getUserText();
std::wstring getFontPath();
bool addFontToSystem(const std::wstring& fontPath);
void setConsoleFont(const Font& font);
Font chooseFont();

int main() {
    // Налаштування кодування для Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    _setmode(_fileno((__acrt_iob_func(1))), _O_U16TEXT);
    _setmode(_fileno(stdin), 0x20000);

    Screen screen(800, 600);

    Font selectedFont = chooseFont();
    if (selectedFont.getSize() == 0) {
        return 1; // Вихід з програми, якщо не вдалося додати шрифт
    }

    // Зміна шрифта консолі
    setConsoleFont(selectedFont);

    // Вибір кольору
    Color selectedColor = selectColor();

    // Вибір швидкості тексту
    int speed = selectSpeed();

    // Вибір ефекту
    int effectChoice = selectEffect();

    // Отримання тексту від користувача і додавання пробілу в кінці
    std::wstring userText = getUserText() + L" ";

    Message message(userText, selectedFont, selectedColor);

    // Вибір ефекту
    DisplayEffect* effect;
    if (effectChoice == 1) {
        effect = new TickerEffect();
    }
    else {
        effect = new BlinkEffect();
    }

    DisplayManager displayManager(screen);
    displayManager.displayMessage(message, *effect, speed);

    delete effect;
    return 0;
}

Color selectColor() {
    int r, g, b;
    std::wcout << L"Введіть колір (RGB): ";
    std::wcin >> r >> g >> b;
    return Color(r, g, b);
}

Font selectFont(const std::vector<std::wstring>& availableFonts) {
    std::wcout << L"Наявні шрифти:\n";
    for (size_t i = 0; i < availableFonts.size(); ++i) {
        std::wcout << i + 1 << L". " << availableFonts[i] << L"\n";
    }
    int fontChoice;
    std::wcout << L"Виберіть номер шрифта: ";
    std::wcin >> fontChoice;

    int fontSize;
    std::wcout << L"Введіть розмір шрифта: ";
    std::wcin >> fontSize;

    return Font(availableFonts[fontChoice - 1], fontSize);
}

int selectSpeed() {
    int speed;
    std::wcout << L"Введіть швидкість (мс) між кадрами: ";
    std::wcin >> speed;
    return speed;
}

int selectEffect() {
    int effectChoice;
    std::wcout << L"Виберіть ефект:\n1. Біжачий рядок\n2. Мигання\n";
    std::wcin >> effectChoice;
    return effectChoice;
}

std::wstring getUserText() {
    std::wcin.ignore();  // Ігнорувати залишки в буфері
    std::wcout << L"Введіть текст: ";
    std::wstring text;
    std::getline(std::wcin, text);
    return text;
}

std::wstring getFontPath() {
    std::wcin.ignore();  // Ігнорувати залишки в буфері
    std::wcout << L"Введіть шлях до файлу шрифту: ";
    std::wstring fontPath;
    std::getline(std::wcin, fontPath);
    return fontPath;
}

bool addFontToSystem(const std::wstring& fontPath) {
    int ret = AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL);
    return ret > 0;
}

void setConsoleFont(const Font& font) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    cfi.nFont = 0;
    wcsncpy_s(cfi.FaceName, LF_FACESIZE, font.getName().c_str(), _TRUNCATE);
    cfi.dwFontSize.Y = font.getSize();
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

Font chooseFont() {
    int fontChoice;
    std::wcout << L"Виберіть опцію:\n1. Вибрати шрифт з наявного списку\n2. Додати новий шрифт\n";
    std::wcin >> fontChoice;

    if (fontChoice == 1) {
        std::vector<std::wstring> availableFonts = { L"Arial", L"Courier New", L"Times New Roman", L"Verdana" };
        return selectFont(availableFonts);
    }
    else if (fontChoice == 2) {
        std::wstring fontPath = getFontPath();
        if (addFontToSystem(fontPath)) {
            std::wcout << L"Шрифт успішно додано.\n";
            int fontSize;
            std::wcout << L"Введіть розмір шрифта: ";
            std::wcin >> fontSize;
            return Font(fontPath.substr(fontPath.find_last_of(L"\\/") + 1), fontSize);
        }
        else {
            std::wcout << L"Не вдалося додати шрифт.\n";
            return Font(L"", 0); // Повертає нульовий розмір, щоб позначити невдачу
        }
    }
    else {
        std::wcout << L"Неправильний вибір.\n";
        return Font(L"", 0); // Повертає нульовий розмір, щоб позначити невдачу
    }
}