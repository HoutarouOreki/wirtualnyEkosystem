#include <iostream>
#include <string>
#include <cstdlib>
#include "srodowisko.h"
#include "funkcjeUtility.h"
#include "glon.h"
#include "grzyb.h"
#include "bakteria.h"
#include "termcolor/termcolor.hpp"

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
    obecnyTryb = 10;
    iloscGlonow = 0;
    iloscGrzybow = 0;
    iloscBakterii = 0;
    iloscMartwych = 0;

    wyswietlajNajedzenie[0] = false;
    wyswietlajNajedzenie[1] = false;
    wyswietlajNajedzenie[2] = false;
    wyswietlajRozmnozenie[0] = false;
    wyswietlajRozmnozenie[1] = false;
    wyswietlajRozmnozenie[2] = false;
    wyswietlajInfo[0] = false;
    wyswietlajInfo[1] = true;
    wyswietlajInfo[2] = true;

    szerokosc = funkcjeUtility::pobierzIntMinMax("szerokosc srodowiska", 3, 20);
    wysokosc = funkcjeUtility::pobierzIntMinMax("wysokosc srodowiska", 3, 20);
    nisze = new Organizm*[szerokosc * wysokosc];
    fill_n(nisze, szerokosc * wysokosc, nullptr);
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
    maxWiekGlonow = funkcjeUtility::wylosujInt(6, 10);
    maxWiekGrzybow = funkcjeUtility::wylosujInt(18, 30);
    maxWiekBakterii = funkcjeUtility::wylosujInt(14, 18);
    maxNajedzenieGlonow = funkcjeUtility::wylosujInt(1, 2);
    maxNajedzenieGrzybow = funkcjeUtility::wylosujInt(4, 6);
    maxNajedzenieBakterii = funkcjeUtility::wylosujInt(2, 4);
    kosztNarodzinGlonow = funkcjeUtility::wylosujInt(1, 2);
    kosztNarodzinGrzybow = funkcjeUtility::wylosujInt(2, (maxNajedzenieGrzybow + 2) / 2);
    kosztNarodzinBakterii = funkcjeUtility::wylosujInt(2, (maxNajedzenieBakterii + 2) / 2);
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
    for (unsigned int i = 0; i < iloscBakterii; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Bakteria(maxWiekBakterii, maxNajedzenieBakterii, kosztNarodzinBakterii);
    }
    std::cin.clear();
    std::cin.ignore();
}

void Srodowisko::wyswietlUstawienia()
{
    std::cout << "Ustawienia" << std::endl << std::endl;
    std::cout << " Sygn. jedzenia (J) " << " Sygn. rozmnozenia (R) " << " Informacje (I) "
              << std::endl;
    std::cout << termcolor::green
              << "    glony = ";
    wyswietlBoolUstawien(wyswietlajNajedzenie[0], termcolor::green);
    std::cout << "     " << "     glony = ";
    wyswietlBoolUstawien(wyswietlajRozmnozenie[0], termcolor::green);
    std::cout << "       " << "    glony = ";
    wyswietlBoolUstawien(wyswietlajInfo[0], termcolor::green);
    std::cout << std::endl << termcolor::blue
              << "   grzyby = ";
    wyswietlBoolUstawien(wyswietlajNajedzenie[1], termcolor::blue);
    std::cout << "     " << "    grzyby = ";
    wyswietlBoolUstawien(wyswietlajRozmnozenie[1], termcolor::blue);
    std::cout << "       " << "   grzyby = ";
    wyswietlBoolUstawien(wyswietlajInfo[1], termcolor::blue);
    std::cout << std::endl << termcolor::red
              << " bakterie = ";
    wyswietlBoolUstawien(wyswietlajNajedzenie[2], termcolor::red);
    std::cout << "     " << "  bakterie = ";
    wyswietlBoolUstawien(wyswietlajRozmnozenie[2], termcolor::red);
    std::cout << "       " << " bakterie = ";
    wyswietlBoolUstawien(wyswietlajInfo[2], termcolor::red);
    std::cout << std::endl << std::endl << termcolor::reset
              << "Aby zmienic dane ustawienie, wpisz pierwsza litere podazana przez"
              << std::endl << "odpowiednia liczbe: 0 = glon, 1 = grzyb, 2 = bakteria"
              << std::endl << "Np. J0 aby zmienic wyswietlanie sygnalu jedzenia dla glonow"
              << std::endl << std::endl;
}

void Srodowisko::wyswietlBoolUstawien(bool zmienna, std::basic_ostream<char>& f(std::basic_ostream<char>&))
{
    if (zmienna) {
        std::cout << termcolor::cyan << "tak";
    } else {
        std::cout << termcolor::magenta << "nie";
    }
    f(std::cout);
}

unsigned int dostanNrOrganizmu(char znakOrganizmu)
{
    unsigned int nrOrganizmu = 0;
    switch (znakOrganizmu) {
    case '*':
        nrOrganizmu = 0;
        break;
    case '#':
        nrOrganizmu = 1;
        break;
    case '@':
        nrOrganizmu = 2;
        break;
    }
    return nrOrganizmu;
}

bool Srodowisko::czyWyswietlacInfo(char znakOrganizmu) const
{
    return wyswietlajInfo[dostanNrOrganizmu(znakOrganizmu)];
}

bool Srodowisko::czySygnalizowacNajedzenie(char znakOrganizmu) const
{
    return wyswietlajNajedzenie[dostanNrOrganizmu(znakOrganizmu)];
}

bool Srodowisko::czySygnalizowacRozmnozenie(char znakOrganizmu) const
{
    return wyswietlajRozmnozenie[dostanNrOrganizmu(znakOrganizmu)];
}

std::string* Srodowisko::informacjeOrganizmow() const
{
    string* linie = new string[szerokosc * wysokosc];
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr || !czyWyswietlacInfo(nisze[i]->dostanZnak())) {
            linie[i] = "";
            continue;
        }
        unsigned int x = dostanX(i);
        unsigned int y = dostanY(i);
        string litera(1, (char)('A' + x));
        string liczba = to_string(y + 1);
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
        string wiek = (nisze[i]->getWiek() < 10 ? " " : "") + to_string(nisze[i]->getWiek());
        string maxWiek = to_string(nisze[i]->getMaxWiek()) + (nisze[i]->getMaxWiek() < 10 ? " " : "");
        string najedzenie = (nisze[i]->getNajedzenie() < 10 ? " " : "") + to_string(nisze[i]->getNajedzenie());
        string maxNajedzenie = to_string(nisze[i]->getMaxNajedzenie()) + (nisze[i]->getMaxNajedzenie() < 10 ? " " : "");
        string zmianaNajedzenia = nisze[i]->getWlasnieNajadl() ? "+" :
                                    nisze[i]->getWlasnieRozmnozyl() ? "-" : " ";
        linie[i] = (y + 1 < 10 ? " " : "") + litera + liczba + ": " + nazwa + " | "
                + wiek + "/" + maxWiek + " |   "
                + najedzenie + "/" + maxNajedzenie + zmianaNajedzenia + "  ";
    }
    return linie;
}

bool Srodowisko::upewnijSieCzyOrganizmNadalIstnieje(int i)
{
    // bakterie mogły zjeść inne organizmy żywe, więc trzeba upewniać się czy organizm jeszcze żyje
    if (nisze[pozycjeZywychOrganizmow[i]] == nullptr) {
        pozycjeZywychOrganizmow.erase(pozycjeZywychOrganizmow.begin() + i);
        return false;
    }
    return true;
}

void Srodowisko::wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko)
{
    if (czyOstatnioDrukowanoSrodowisko) {
        int linia;
        int kolumna;
        funkcjeUtility::dostanPozycjeKursora(&kolumna, &linia);
        funkcjeUtility::ustawKursor(0, linia - 18 - wysokosc);
        std::cout << std::endl;
        // cout << "linia: " << linia << ", kolumna: " << kolumna << endl;
    }
    std::cout << "Krokow symulacji: " << krokSymulacji << std::endl << std::endl;
    std::cout << " Ilosc glonow:   " << iloscGlonow << "    " << std::endl
              << " Ilosc grzybow:  " << iloscGrzybow << "    " << std::endl
              << " Ilosc bakterii: " << iloscBakterii << "    " << std::endl
              << " Ilosc martwych: " << iloscMartwych << "    " << std::endl << std::endl;
    string* informacje = informacjeOrganizmow();
    unsigned int indeksInformacji = 0;
    std::cout << "Wyswietlanie srodowiska" << std::endl << std::endl;
    for (unsigned char i = 'A'; i < 'A' + szerokosc; i++) {
        if (i == 'A') {
            std::cout << "   ";
        }
        std::cout << i << " ";
    }
    std::cout << " |  Poz: nazwa    |  wiek | najedzenie" << std::endl;
    char znak;
    for (unsigned int i = 0; i < wysokosc; i++) {
        if (i + 1 < 10) {
            std::cout << " ";
        }
        std::cout << i + 1 << " ";
        for (unsigned int j = 0; j < szerokosc; j++) {
            std::cout << termcolor::on_grey;
            if (getNisza(j, i) == nullptr) {
                std::cout << termcolor::grey << "-";
            } else {
                znak = getNisza(j, i)->dostanZnak();
                if (czySygnalizowacRozmnozenie(getNisza(j, i)->dostanZnak()) &&
                        getNisza(j, i)->getWlasnieRozmnozyl()) {
                    std::cout << termcolor::on_magenta;
                } else if (czySygnalizowacNajedzenie(getNisza(j, i)->dostanZnak()) &&
                           getNisza(j, i)->getWlasnieNajadl()) {
                    std::cout << termcolor::on_yellow;
                }
                switch (znak) {
                case '*': // glon
                    std::cout << termcolor::green;
                    break;
                case '#': // grzyb
                    std::cout << (getNisza(j, i)->getWlasnieNajadl() &&
                                  czySygnalizowacNajedzenie(getNisza(j, i)->dostanZnak()) ?
                                      termcolor::blue : termcolor::cyan);
                    break;
                case '@': // bakteria
                    std::cout << termcolor::red;
                    break;
                case '+': // zwloki
                    std::cout << termcolor::yellow;
                    break;
                default: // nieznany
                    std::cout << termcolor::cyan;
                    break;
                }
                std::cout << znak;
            }
            std::cout << termcolor::on_grey << (j == szerokosc - 1 ? "" : " ");
        }
        std::cout << termcolor::reset;
        while (indeksInformacji < szerokosc * wysokosc && informacje[indeksInformacji].length() == 0) {
            indeksInformacji++;
        }
        if (indeksInformacji < szerokosc * wysokosc) {
            std::cout << "  |  " << informacje[indeksInformacji];
            indeksInformacji++;
        } else {
            std::cout << "                                      ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Srodowisko::petla()
{
    std::cin.clear();
    string wejscie = "";
    bool pierwszeWejscie = true;
    bool ostatnioDrukowanoSrodowisko = false;
    while (wejscie != "E") {
        std::cout << "Enter bez znakow - wykonanie kroku symulacji i wyswietlenie srodowiska"
                  << std::endl << "s - wyswietlenie srodowiska"
                  << std::endl << "u - wyswietlenie ustawien"
                  << std::endl << "e - wyjscie z programu"
                  << std::endl;

        wejscie = pierwszeWejscie ? "S" : funkcjeUtility::dostanLinie();
        pierwszeWejscie = false;

        // zamiana wejścia na duże litery
        for (auto & c: wejscie) {
            c = std::toupper(c);
        }

        if (!(ostatnioDrukowanoSrodowisko && (wejscie == "S" || wejscie == ""))) {
            std::cout << std::endl << "-----------------------" << std::endl;
        }

        if (wejscie == "") {
            obecnyTryb = 0;
        } else if (wejscie == "S") {
            obecnyTryb = 1;
        } else if (wejscie == "U") {
            obecnyTryb = 2;
        } else if (wejscie == "E") {
            return;
        } else if (wejscie.length() == 2 && wejscie[1] >= '0' && wejscie[1] <= '2') {
            switch (wejscie[0]) {
            case 'J':
                funkcjeUtility::przelaczBool(&wyswietlajNajedzenie[(unsigned int)(wejscie[1] - '0')]);
                break;
            case 'R':
                funkcjeUtility::przelaczBool(&wyswietlajRozmnozenie[(unsigned int)(wejscie[1] - '0')]);
                break;
            case 'I':
                funkcjeUtility::przelaczBool(&wyswietlajInfo[(unsigned int)(wejscie[1] - '0')]);
                break;
            }
        } else {
            obecnyTryb = 3;
        }
        switch (obecnyTryb) {
        case 0:
            wykonajKrokSymulacji();
            wyswietlSrodowisko(ostatnioDrukowanoSrodowisko);
            break;
        case 1:
            wyswietlSrodowisko(ostatnioDrukowanoSrodowisko);
            break;
        case 2:
            wyswietlUstawienia();
            break;
        }
        ostatnioDrukowanoSrodowisko = obecnyTryb <= 1;
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
    Organizm* obecnyOrganizm;

    // udostępnianie organizmom informacji o otoczeniu oraz zgromadzenie
    // informacji o żywych organizmach do przyspieszenia iteracji czynności życiowych
    pozycjeZywychOrganizmow.clear();
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr || !nisze[i]->bCzyZyje()) {
            continue;
        }

        pozycjeZywychOrganizmow.push_back(i);

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
        int nSasiednichNiszy = 0;
        for (int j = 0; j < 8; j++) {
            if (sasiedzi[j]) {
                nSasiednichNiszy++;
            }
        }
        unsigned int pozycjeSasiednichNiszy[nSasiednichNiszy];
        unsigned int k = 0;
        for (int j = 0; j < 8; j++) {
            if (sasiedzi[j]) {
                pozycjeSasiednichNiszy[k] = dostanIndeksSasiada(x, y, j);
                k++;
            }
        }
        obecnyOrganizm = nisze[i];
        obecnyOrganizm->zobaczSrodowisko(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy);
    }

    // wywołanie możliwych prób rozmnażania się u organizmów
    for (unsigned int i = 0; i < pozycjeZywychOrganizmow.size(); i++) {
        obecnyOrganizm = nisze[pozycjeZywychOrganizmow[i]];
        if (obecnyOrganizm->bCzyZyje() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeRozmnozSie();
        }
    }

    // wywołanie możliwych prób najedzenia się u organizmów
    for (unsigned int i = 0; i < pozycjeZywychOrganizmow.size(); i++) {
        if (!upewnijSieCzyOrganizmNadalIstnieje(i)) {
            i--;
            continue;
        }
        obecnyOrganizm = nisze[pozycjeZywychOrganizmow[i]];
        if (obecnyOrganizm->bCzyZyje() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeSprobujNajescSie();
        }
    }

    // wywołanie starzenia się u organizmów
    for (unsigned int i = 0; i < pozycjeZywychOrganizmow.size(); i++) {
        if (!upewnijSieCzyOrganizmNadalIstnieje(i)) {
            i--;
            continue;
        }
        obecnyOrganizm = nisze[pozycjeZywychOrganizmow[i]];
        obecnyOrganizm->starzenieSie();
    }

    // wywołanie możliwych prób poruszenia się u organizmów
    for (unsigned int i = 0; i < pozycjeZywychOrganizmow.size(); i++) {
        obecnyOrganizm = nisze[pozycjeZywychOrganizmow[i]];
        if (obecnyOrganizm->bCzyZyje() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeSprobujPoruszycSie();
        }
    }
    krokSymulacji++;

    podliczIlosciOrganizmow();
}

void Srodowisko::podliczIlosciOrganizmow()
{
    iloscGlonow = iloscGrzybow = iloscBakterii = iloscMartwych = 0;
    for (unsigned int i = 0; i < szerokosc * wysokosc; i++) {
        if (nisze[i] == nullptr) {
            continue;
        }
        switch (nisze[i]->dostanZnak()) {
        case Organizm::ZNAK_GLONU:
            iloscGlonow++;
            break;
        case Organizm::ZNAK_GRZYBU:
            iloscGrzybow++;
            break;
        case Organizm::ZNAK_BAKTERII:
            iloscBakterii++;
            break;
        case Organizm::ZNAK_MARTWEGO:
            iloscMartwych++;
            break;
        }
    }
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
