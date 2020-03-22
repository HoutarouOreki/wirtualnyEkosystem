#include <iostream>
#include <string>

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

    std::string nacisnijDowolnyKlawisz()
    {
        std::string temp;
        std::cout << "Nacisnij enter...";
        getline(std::cin, temp);
        return temp;
    }
}
