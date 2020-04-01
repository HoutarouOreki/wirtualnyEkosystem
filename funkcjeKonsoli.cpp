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
    void dostanPozycjeKursora(unsigned int* kolumna, unsigned int* linia)
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
        std::cout << "\033[" << linia + 1 << ";" << kolumna + 1 << "H";
    #endif
    }

    void powiekszOkno(unsigned int minSzerokosc, unsigned int minWysokosc)
    {
    #if defined (KONSOLA_WINDOWS)
        HANDLE hKonsoli = GetStdHandle(STD_OUTPUT_HANDLE);
        HWND konsola = GetConsoleWindow();

        RECT prostokatKonsoli;
        GetWindowRect(konsola, &prostokatKonsoli);
        CONSOLE_FONT_INFO infoCzcionki;
        GetCurrentConsoleFont(hKonsoli, false, &infoCzcionki);
        COORD wielkoscCzcionki = GetConsoleFontSize(hKonsoli, infoCzcionki.nFont);

        minSzerokosc = std::max(prostokatKonsoli.right - prostokatKonsoli.left,
                                (long)minSzerokosc * wielkoscCzcionki.X);
        minWysokosc = std::max(prostokatKonsoli.bottom - prostokatKonsoli.top,
                               (long)minWysokosc * wielkoscCzcionki.Y);
        MoveWindow(konsola, prostokatKonsoli.left, prostokatKonsoli.top, minSzerokosc, minWysokosc, TRUE);
    #elif defined (KONSOLA_LINUX) || defined (KONSOLA_MAC)
        // dostań wielkość konsoli
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        // jeśli dany wymiar konsoli jest mniejszy niż pożądany, powiększ
        std::cout << "\e[8;" << std::max(minWysokosc, (unsigned int)w.ws_row) << ";"
                  << std::max(minSzerokosc, (unsigned int)w.ws_col) << "t";
#endif
    }

    void cofnijKursor(unsigned int iloscLinii)
    {
        unsigned int x, y;
        dostanPozycjeKursora(&x, &y);
        ustawKursor(0, y - iloscLinii);
    }

}
