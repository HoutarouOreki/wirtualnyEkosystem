#include <iostream>
#include <string>
#include "funkcjeUtility.h"

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
            nazwa = nazwa + " (od " + std::to_string(min) +
                    " do " + std::to_string(max) + ")";
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

    void przelaczBool(bool* zmienna)
    {
        *zmienna = !*zmienna;
    }
}
