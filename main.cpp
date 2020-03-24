#include "funkcjeUtility.h"
#include "funkcjeKonsoli.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "srodowisko.h"

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
    const unsigned int wysokosc_wyswietlania = 43;
    funkcjeKonsoli::ustawWielkoscKonsoli(130, wysokosc_wyswietlania);
    srand(time(nullptr));
    ustawDomyslneUstawieniaWyswietlania(&ustawieniaWyswietlania);
    std::cout << "Wirtualny Ekosystem                                              Wirtualny Ekosystem"
              << std::endl;
    for (unsigned int i = 0; i < wysokosc_wyswietlania - 7; i++) {
        std::cout << std::endl;
    }

    std::cout << "Powieksz okno tak, aby napisy na gorze oraz ten mogly byc jednoczesnie widoczne"
              << std::endl << "(oba gorne powinny sie zmiescic w jednej linii), nastepnie wcisnij enter";
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
