#include "funkcjeUtility.h"
#include "funkcjeKonsoli.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "srodowisko.h"

/// \mainpage Wirtualny Ekosystem
/// Program ten pozwala na utworzenie własnego \ref Srodowisko "środowiska".
/// W środowisku żyją sobie \ref Organizm "organizmy" które jedzą, rozmnażają oraz poruszają się.
/// Ich \ref Organizm::maxWiek "maksymalny wiek", \ref Organizm::maxNajedzenie "maksymalny poziom najedzenia"
/// oraz \ref Organizm::kosztNarodzin "koszt potomka" są losowane przy
/// \ref Srodowisko::Srodowisko(ustawieniaWyswietlania* ustawieniaWyswietlania) "utworzeniu środowiska".
/// \li Zielone \ref Glon "glony" to organizmy pasywne żywiące się fotosyntezą i nieporuszające się.
/// \li Niebieskie \ref Grzyb "grzyby" jedzą martwe organizmy (które przekroczyły swój maksymalny wiek)
/// i przemieszczają się, gdy nie uda im się rozmnożyć ani pożywić.
/// \li Czerwone \ref Bakteria "bakterie" żywią się glonami,
/// bądź innymi bakteriami jak nie znajdą glonów,
/// i zajmują miejsce wchłoniętego przez siebie organizmu.

Srodowisko* srodowisko;
Srodowisko::ustawieniaWyswietlania ustawieniaWyswietlania;

void ustawDomyslneUstawieniaWyswietlania(Srodowisko::ustawieniaWyswietlania *ustawieniaWyswietlania)
{
    ustawieniaWyswietlania->wyswietlajNajedzenie[0] = false;
    ustawieniaWyswietlania->wyswietlajNajedzenie[1] = false;
    ustawieniaWyswietlania->wyswietlajNajedzenie[2] = false;
    ustawieniaWyswietlania->wyswietlajRozmnozenie[0] = false;
    ustawieniaWyswietlania->wyswietlajRozmnozenie[1] = false;
    ustawieniaWyswietlania->wyswietlajRozmnozenie[2] = false;
    ustawieniaWyswietlania->wyswietlajInfo[0] = false;
    ustawieniaWyswietlania->wyswietlajInfo[1] = true;
    ustawieniaWyswietlania->wyswietlajInfo[2] = true;
    ustawieniaWyswietlania->nadrysowywanie = true;
}

int main()
{
    const unsigned int wysokosc_wyswietlania = 44;
    funkcjeKonsoli::powiekszOkno(130, wysokosc_wyswietlania);
    srand(time(nullptr));
    ustawDomyslneUstawieniaWyswietlania(&ustawieniaWyswietlania);
    std::cout << "Wirtualny Ekosystem" << std::endl << "Wcisnij enter...";
    std::string wejscie;
    std::getline(std::cin, wejscie);

    while (wejscie != "e" && wejscie != "E") {
        srodowisko = new Srodowisko(&ustawieniaWyswietlania);
        srodowisko->petla();

        // w tym miejscu pętla dotychczasowego środowiska zakończyła się
        delete srodowisko;
        std::cout << "Opuszczono srodowisko" << std::endl
                  << "u = utworz nowe" << std::endl
                  << "e = zakoncz program" << std::endl;
        do {
            std::cout << ">";
            std::cin >> wejscie;
        } while (wejscie != "u" && wejscie != "U" && wejscie != "e" && wejscie != "E");
    }
    return 0;
}
