#include <iostream>
#include <string>
#include <cstdlib>
#include "srodowisko.h"
#include "funkcjeUtility.h"
#include "glon.h"
#include "grzyb.h"

using namespace std;

unsigned int Srodowisko::getSzerokosc() const
{
    return szerokosc;
}

unsigned int Srodowisko::getWysokosc() const
{
    return wysokosc;
}

Organizm* Srodowisko::getNisza(unsigned int x, unsigned int y) const
{
    return nisze[dostanIndeks(x, y)];
}

void Srodowisko::setNisza(Organizm *organizm, unsigned int x, unsigned int y)
{
    nisze[dostanIndeks(x, y)] = organizm;
}

Srodowisko::Srodowisko()
{
    krokSymulacji = 0;
    szerokosc = funkcjeUtility::pobierzIntMinMax("szerokosc srodowiska", 3, 20);
    wysokosc = funkcjeUtility::pobierzIntMinMax("wysokosc srodowiska", 3, 20);
    nisze = new Organizm*[szerokosc * wysokosc] { nullptr };
    unsigned int iloscNisz = szerokosc * wysokosc;
    unsigned int iloscGlonow, iloscGrzybow, iloscBakterii;
    bool bDopuszczalnaIloscOrganizmow = false;
    while (!bDopuszczalnaIloscOrganizmow) {
        iloscGlonow = funkcjeUtility::pobierzIntMinMax("ilosc glonow", 0, iloscNisz);
        iloscGrzybow = funkcjeUtility::pobierzIntMinMax("ilosc grzybow", 0, iloscNisz);
        iloscBakterii = funkcjeUtility::pobierzIntMinMax("ilosc bakterii", 0, iloscNisz);
        if (iloscGlonow + iloscGrzybow + iloscBakterii <= iloscNisz) {
            bDopuszczalnaIloscOrganizmow = true;
        } else {
            std::cout << "Podales ilosc organizmow przekraczajaca ilosc dostepnych nisz ("
                      << iloscGlonow + iloscGrzybow + iloscBakterii << " > " << iloscNisz << ")"
                      << std::endl;
        }
    }
    int wylosowanaNisza;
    maxWiekGlonow = funkcjeUtility::wylosujInt(4, 5);
    maxWiekGrzybow = funkcjeUtility::wylosujInt(18, 30);
    maxWiekBakterii = funkcjeUtility::wylosujInt(5, 20);
    maxNajedzenieGlonow = funkcjeUtility::wylosujInt(2, maxWiekGlonow - 2);
    maxNajedzenieGrzybow = funkcjeUtility::wylosujInt(2, 6);
    maxNajedzenieBakterii = funkcjeUtility::wylosujInt(2, maxWiekBakterii - 3);
    kosztNarodzinGlonow = funkcjeUtility::wylosujInt(2, (maxNajedzenieGlonow + 2) / 2);
    kosztNarodzinGrzybow = funkcjeUtility::wylosujInt(2, (maxNajedzenieGrzybow + 2) / 2);
    kosztNarodzinBakterii = funkcjeUtility::wylosujInt(2, maxNajedzenieBakterii);
    for (unsigned int i = 0; i < iloscGlonow; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Glon(maxWiekGlonow, maxNajedzenieGlonow, kosztNarodzinGlonow);
    }
    for (unsigned int i = 0; i < iloscGrzybow; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Grzyb(maxWiekGrzybow, maxNajedzenieGrzybow, kosztNarodzinGrzybow);
    }
}

std::string* Srodowisko::informacjeOrganizmow() const
{
    string* linie = new string[szerokosc * wysokosc];
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr) {
            linie[i] = "";
            continue;
        }
        unsigned int x = dostanX(i);
        unsigned int y = dostanY(i);
        string litera(1, (char)('A' + x));
        string liczba = to_string(y);
        string nazwa;
        switch (nisze[i]->dostanZnak()) {
        case '*':
            nazwa = "glon    ";
            break;
        case '#':
            nazwa = "grzyb   ";
            break;
        case '@':
            nazwa = "bakteria";
            break;
        case '+':
            nazwa = "zwloki  ";
            break;
        default:
            nazwa = "nieznany";
            break;
        }
        linie[i] = (y < 10 ? " " : "") + litera + liczba + ": " + nazwa + " | wiek "
                + to_string(nisze[i]->getWiek()) + "/" + to_string(nisze[i]->getMaxWiek()) + " | najedzenie "
                + to_string(nisze[i]->getNajedzenie()) + "/" + to_string(nisze[i]->getMaxNajedzenie());
    }
    return linie;
}

void Srodowisko::wyswietlSrodowisko()
{
    string* informacje = informacjeOrganizmow();
    unsigned int indeksInformacji = 0;
    std::cout << "Wyswietlanie srodowiska" << std::endl << std::endl;
    for (unsigned char i = 'A'; i < 'A' + szerokosc; i++) {
        if (i == 'A') {
            std::cout << "   ";
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (unsigned int i = 0; i < wysokosc; i++) {
        if (i + 1 < 10) {
            std::cout << " ";
        }
        std::cout << i + 1 << " ";
        for (unsigned int j = 0; j < szerokosc; j++) {
            if (getNisza(j, i) == nullptr) {
                std::cout << "-" << " ";
            } else {
                std::cout << getNisza(j, i)->dostanZnak() << " ";
            }
        }
        while (indeksInformacji < szerokosc * wysokosc && informacje[indeksInformacji].length() == 0) {
            indeksInformacji++;
        }
        if (indeksInformacji < szerokosc * wysokosc) {
            std::cout << "  |  " << informacje[indeksInformacji];
            indeksInformacji++;
        }
        std::cout << std::endl;
    }
}

void Srodowisko::rozpocznijPetle()
{
    string wejscie = "";
    while (wejscie != "wyjdz") {
        std::cout << "Krokow symulacji: " << krokSymulacji << std::endl << std::endl;
        wyswietlSrodowisko();
        std::cout << std::endl;
        wejscie = funkcjeUtility::nacisnijDowolnyKlawisz();
        wykonajKrokSymulacji();
    }
}

Srodowisko::~Srodowisko()
{
    for (unsigned int i = 0; i < szerokosc * wysokosc; i++) {
        delete nisze[i];
    }
    delete [] nisze;
}

void Srodowisko::wykonajKrokSymulacji()
{
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr) {
            continue;
        }
        nisze[i]->wlasnyIndeks = i;
        bool sasiedzi[8];
        std::fill_n(sasiedzi, 8, true);
        unsigned int x = dostanX(i);
        if (x == 0) {
            sasiedzi[0] = sasiedzi[3] = sasiedzi[5] = false;
        }
        if (x == szerokosc - 1) {
            sasiedzi[2] = sasiedzi[4] = sasiedzi[7] = false;
        }
        unsigned int y = dostanY(i);
        if (y == 0) {
            sasiedzi[0] = sasiedzi[1] = sasiedzi[2] = false;
        }
        if (y == wysokosc - 1) {
            sasiedzi[5] = sasiedzi[6] = sasiedzi[7] = false;
        }
        int nSasiadow = 0;
        for (int j = 0; j < 8; j++) {
            if (sasiedzi[j]) {
                nSasiadow++;
            }
        }
        int pozycjeSasiadow[nSasiadow];
        int k = 0;
        for (int j = 0; j < 8; j++) {
            if (sasiedzi[j]) {
                pozycjeSasiadow[k] = dostanIndeksSasiada(x, y, j);
                k++;
            }
        }
        nisze[i]->krokSymulacji(nisze, pozycjeSasiadow, nSasiadow);
    }
    krokSymulacji++;
}

unsigned int Srodowisko::dostanX(int indeksNiszy) const
{
    return indeksNiszy % szerokosc;
}

unsigned int Srodowisko::dostanY(int indeksNiszy) const
{
    return indeksNiszy / szerokosc;
}

unsigned int Srodowisko::dostanIndeks(unsigned int x, unsigned int y) const
{
    return (y * szerokosc) + x;
}

unsigned int Srodowisko::dostanIndeksSasiada(unsigned int x, unsigned int y, unsigned int nrSasiada) const
{
    if (nrSasiada < 3) {
        y--;
    } else if (nrSasiada > 4) {
        y++;
    }
    if (nrSasiada == 0 || nrSasiada == 3 || nrSasiada == 5) {
        x--;
    } else if (nrSasiada != 1 && nrSasiada != 6) {
        x++;
    }
    return dostanIndeks(x, y);
}
