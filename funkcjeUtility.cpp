#include <iostream>
#include <string>
#include "funkcjeUtility.h"
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

namespace funkcjeUtility {
    int pobierzInt(std::string nazwa) {
        std::string linia;
        int wartosc;
        while (true) {
            std::cout << "Podaj " << nazwa << std::endl << ">";
            std::cin >> linia;
            try {
                wartosc = stoi(linia);
            } catch (const std::invalid_argument&) {
                std::cout << "Nie podano prawidlowej liczby calkowitej." << std::endl;
                continue;
            }
            return wartosc;
        }
    }

    int pobierzIntMinMax(std::string nazwa, int min, int max) {
        int wartosc;
        do {
            wartosc = pobierzInt(nazwa);
            if (wartosc < min || wartosc > max) {
                std::cout << "Podano wartosc spoza dozwolonego zakresu <"
                          << min << ", " << max << ">." << std::endl;
            }
        } while (wartosc < min || wartosc > max);
        return wartosc;
    }

    int wylosujInt(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    std::string dostanLinie()
    {
        std::string temp;
        std::cout << ">";
        getline(std::cin, temp);
        return temp;
    }

    void przelaczBool(bool* wartosc)
    {
        *wartosc = !*wartosc;
    }

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

    std::string liczbaBialeZnaki(int liczba, unsigned int lacznaIloscZnakow, bool liczbaPoPrawej)
    {
        int absLiczba = liczba;
        if (liczba < 0) {
            lacznaIloscZnakow--;
            absLiczba = -liczba;
        }

        do {
            lacznaIloscZnakow--;
            absLiczba /= 10;
        } while (absLiczba != 0);

        std::string bialeZnaki = "";
        for (unsigned int i = 0; i < lacznaIloscZnakow; i++) {
            bialeZnaki += " ";
        }
        std::string liczbaString = std::to_string(liczba);
        return liczbaPoPrawej ? (bialeZnaki + liczbaString) : (liczbaString + bialeZnaki);
    }

    std::string ilesBialychZnakow(unsigned int ile)
    {
        std::string s;
        for (unsigned int i = 0; i < ile; i++) {
            s += " ";
        }
        return s;
    }

}
