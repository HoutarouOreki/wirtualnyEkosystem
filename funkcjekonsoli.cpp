#include "funkcjeKonsoli.h"
#include "termcolor/termcolor.hpp"

// wykrycie systemu
#if defined(_WIN32) || defined(_WIN64)
#   define KONSOLA_WINDOWS
#elif defined(__APPLE__)
#   define KONSOLA_MAC
#elif defined(__unix__) || defined(__unix)
#   define KONSOLA_LINUX
#endif

#if defined(KONSOLA_MAC) || defined(KONSOLA_LINUX)
#   include <unistd.h>
#   include <termios.h>
#   include <sys/ioctl.h>
#   include <stdio.h>
#elif defined(KONSOLA_WINDOWS)
#   include <io.h>
#   include <windows.h>
#endif

namespace funkcjeKonsoli {
    void dostanPozycjeKursora(int* kolumna, int* linia)
    {
    #if defined (KONSOLA_WINDOWS)
        struct _CONSOLE_SCREEN_BUFFER_INFO infoBufora;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsole, &infoBufora);
        *kolumna = infoBufora.dwCursorPosition.X;
        *linia = infoBufora.dwCursorPosition.Y;
    #elif defined (KONSOLA_LINUX) || defined (KONSOLA_MAC)
        struct winsize size;
        if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
            printf("TIOCGWINSZ error");
        *linia = size.ws_row;
        *kolumna = size.ws_col;
    #endif
    }

    void ustawKursor(int kolumna, int linia)
    {
    #if defined (KONSOLA_WINDOWS)
        COORD koord;
        koord.X = kolumna + 1;
        koord.Y = linia + 1;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleCursorPosition(hConsole, koord);
    #elif defined (KONSOLA_LINUX) || defined (KONSOLA_MAC)
        printf("\033[%d;%dH",linia+1,kolumna+1);
    #endif
    }

    void ustawWielkoscKonsoli(unsigned int x, unsigned int y)
    {
    #if defined (KONSOLA_WINDOWS)
        HANDLE hKonsoli = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFO infoCzcionki;
        GetCurrentConsoleFont(hKonsoli, false, &infoCzcionki);
        COORD wielkoscCzcionki = GetConsoleFontSize(hKonsoli, infoCzcionki.nFont);
        std::cout << wielkoscCzcionki.X << " / " << wielkoscCzcionki.Y;
        x *= wielkoscCzcionki.X;
        y *= wielkoscCzcionki.Y;
        HWND konsola = GetConsoleWindow();
        RECT ConsoleRect;
        GetWindowRect(konsola, &ConsoleRect);
        MoveWindow(konsola, ConsoleRect.left, ConsoleRect.top, x, y, TRUE);
    #endif
    }
}
