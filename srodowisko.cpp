#include <iostream>
#include <string>
#include "srodowisko.h"
#include "funkcjeUtility.h"
#include "funkcjeKonsoli.h"
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

Organizm* Srodowisko::getNisza(const unsigned int x, const unsigned int y) const
{
    return nisze[indeksNiszyOdKoordynat(x, y)];
}

void Srodowisko::setNisza(Organizm *const organizm, const unsigned int x, const unsigned int y)
{
    const unsigned int indeks = indeksNiszyOdKoordynat(x, y);
    nisze[indeks] = organizm;
    organizm->wlasnyIndeks = indeks;
}

char Srodowisko::dostanLitereKolumny(unsigned int nrKolumny) const
{
    // wykorzystamy tę zmienną do zwrócenia
    nrKolumny += 64;
    if (nrKolumny > 90) {
        // w tym miejscu przekroczyliśmy literę 'Z', więc powinniśmy
        // pominąć 6 znaków ASCII pomiędzy wielkimi i małymi literami
        nrKolumny += 6;
    }
    return char(nrKolumny);
}

Srodowisko::Srodowisko(ustawieniaWyswietlania *ustWyswietlania)
{
    this->ustWyswietlania = ustWyswietlania;
    krokSymulacji = 0;
    ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::zaden;
    iloscMartwych = 0;

    szerokosc = funkcjeUtility::pobierzIntMinMax("szerokosc srodowiska", 5, MAX_SZEROKOSC);
    wysokosc = funkcjeUtility::pobierzIntMinMax("wysokosc srodowiska", 5, MAX_WYSOKOSC);
    nisze = new Organizm*[szerokosc * wysokosc];
    fill_n(nisze, szerokosc * wysokosc, nullptr);
    const unsigned int iloscNisz = szerokosc * wysokosc;
    bool bDopuszczalnaIloscOrganizmow = false;
    while (!bDopuszczalnaIloscOrganizmow) {
        iloscGlonow = funkcjeUtility::pobierzIntMinMax("ilosc glonow", 0, iloscNisz);
        iloscGrzybow = funkcjeUtility::pobierzIntMinMax("ilosc grzybow", 0, iloscNisz - iloscGlonow);
        iloscBakterii = funkcjeUtility::pobierzIntMinMax("ilosc bakterii", 0, iloscNisz - iloscGlonow - iloscGrzybow);
        if (iloscGlonow + iloscGrzybow + iloscBakterii <= iloscNisz) {
            bDopuszczalnaIloscOrganizmow = true;
        } else {
            std::cout << "Podales ilosc organizmow przekraczajaca ilosc dostepnych nisz ("
                      << iloscGlonow + iloscGrzybow + iloscBakterii << " > " << iloscNisz << ")"
                      << std::endl;
        }
    }
    int wylosowanaNisza;
//    const unsigned int maxWiekGlonow = funkcjeUtility::wylosujInt(10, 12);
//    const unsigned int maxWiekGrzybow = funkcjeUtility::wylosujInt(30, 40);
//    const unsigned int maxWiekBakterii = funkcjeUtility::wylosujInt(15, 20);
//    const unsigned int maxNajedzenieGlonow = funkcjeUtility::wylosujInt(2, 3);
//    const unsigned int maxNajedzenieGrzybow = funkcjeUtility::wylosujInt(5, 10);
//    const unsigned int maxNajedzenieBakterii = funkcjeUtility::wylosujInt(7, 9);
//    const unsigned int kosztNarodzinGlonow = funkcjeUtility::wylosujInt(1, maxNajedzenieGlonow);
//    const unsigned int kosztNarodzinGrzybow = funkcjeUtility::wylosujInt(2, 5);
//    const unsigned int kosztNarodzinBakterii = funkcjeUtility::wylosujInt(5, 7);
    maxWieki[0] = funkcjeUtility::wylosujInt(10, 12);
    maxWieki[1] = funkcjeUtility::wylosujInt(30, 40);
    maxWieki[2] = funkcjeUtility::wylosujInt(7, 9);
    maxNajedzenia[0] = funkcjeUtility::wylosujInt(2, 3);
    maxNajedzenia[1] = funkcjeUtility::wylosujInt(5, 10);
    maxNajedzenia[2] = funkcjeUtility::wylosujInt(15, 25);
    kosztyNarodzin[0] = funkcjeUtility::wylosujInt(1, 2);
    kosztyNarodzin[1] = funkcjeUtility::wylosujInt(2, 4);
    kosztyNarodzin[2] = funkcjeUtility::wylosujInt(2, 3);
    for (unsigned int i = 0; i < iloscGlonow; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Glon(maxWieki[0], maxNajedzenia[0], kosztyNarodzin[0], i == 0 ? 0 : funkcjeUtility::wylosujInt(0, maxWieki[0] / 2));
    }
    for (unsigned int i = 0; i < iloscGrzybow; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Grzyb(maxWieki[1], maxNajedzenia[1], kosztyNarodzin[1], i == 0 ? 0 : funkcjeUtility::wylosujInt(0, maxWieki[1] / 2));
    }
    for (unsigned int i = 0; i < iloscBakterii; i++) {
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscNisz - 1);
        } while (nisze[wylosowanaNisza] != nullptr);
        nisze[wylosowanaNisza] = new Bakteria(maxWieki[2], maxNajedzenia[2], kosztyNarodzin[2], i == 0 ? 0 : funkcjeUtility::wylosujInt(0, maxWieki[2] / 2));
    }

    statystyki.dodajStatystykiOstatniegoKroku(this);

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
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajNajedzenie[0], termcolor::green);
    std::cout << "     " << "     glony = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajRozmnozenie[0], termcolor::green);
    std::cout << "       " << "    glony = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajInfo[0], termcolor::green);
    std::cout << std::endl << termcolor::blue
              << "   grzyby = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajNajedzenie[1], termcolor::blue);
    std::cout << "     " << "    grzyby = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajRozmnozenie[1], termcolor::blue);
    std::cout << "       " << "   grzyby = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajInfo[1], termcolor::blue);
    std::cout << std::endl << termcolor::red
              << " bakterie = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajNajedzenie[2], termcolor::red);
    std::cout << "     " << "  bakterie = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajRozmnozenie[2], termcolor::red);
    std::cout << "       " << " bakterie = ";
    wyswietlBoolUstawien(ustWyswietlania->wyswietlajInfo[2], termcolor::red);
    std::cout << std::endl << std::endl << termcolor::reset
              << "Aby zmieniac powyzsze ustawienia, wpisz odpowiednia litere podazana przez"
              << std::endl << "odpowiednia liczbe: 0 = glon, 1 = grzyb, 2 = bakteria"
              << std::endl << "Np. J0 aby zmienic wyswietlanie sygnalu jedzenia dla glonow"
              << std::endl << std::endl
              << "Nadrysowywanie bufora = " ;
    wyswietlBoolUstawien(ustWyswietlania->nadrysowywanie, termcolor::reset);
    std::cout << std::endl << "Czy kolejne kroki symulacji powinny byc rysowane w miejscu poprzednich."
              << std::endl << "Jesli tak, przy szybkim wykonywaniu krokow konsola nie bedzie \"migac\","
              << std::endl << "jednak nie bedzie tez widac poprzednich krokow symulacji."
              << std::endl << "Wpisz n aby przelaczyc nadrysowywanie bufora"
              << std::endl << std::endl;
}

void Srodowisko::wyswietlInstrukcjeFunkcjiStatystycznych() const
{
    std::cout << std::endl << "sX - wyswietl statystyki ostatnich X krokow, np. s100."
              << std::endl << "se - wyeksportuj statystyki i wlasciwosci srodowiska do pliku csv"
              << std::endl << "w - wyswietl wykres ilosci organizmow dla ostatnich 130 krokow"
              << std::endl << std::endl;
}

void Srodowisko::wyswietlStatystyki(const unsigned int iloscKrokow = 20) const
{
    std::cout << "Statystyki" << std::endl << std::endl
              << "      |             ilosci             ||     najedzone / rozmnozone     |" << std::endl
              << "      |--------------------------------||--------------------------------|" << std::endl
              << " krok |   glony  |  grzyby  | bakterie ||   glony  |  grzyby  | bakterie |" << std::endl
              << "------|----------|----------|----------||----------|----------|----------|" << std::endl;

    for (unsigned int i = std::max(0, (int)krokSymulacji - (int)iloscKrokow + 1); i <= krokSymulacji; i++) {
        std::cout << funkcjeUtility::liczbaBialeZnaki(i, 6, true)
          << "|    " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciGlonow()[i], 4, true)
          << "  |    " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciGrzybow()[i], 4, true)
          << "  |    " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciBakterii()[i], 4, true)
          << "  || " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciGlonow()[i] -
                                                         statystyki.getIlosciRozmnozonychGlonow()[i], 4, true)
          << "/" << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciRozmnozonychGlonow()[i], 4, false)
          << "| " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciNajedzonychGrzybow()[i], 4, true)
          << "/" << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciRozmnozonychGrzybow()[i], 4, false)
          << "| " << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciNajedzonychBakterii()[i], 4, true)
          << "/" << funkcjeUtility::liczbaBialeZnaki(statystyki.getIlosciRozmnozonychBakterii()[i], 4, false)
          << "|" << std::endl;
    }

    wyswietlInstrukcjeFunkcjiStatystycznych();
}

void Srodowisko::wyswietlWykresIlosciOrganizmow() const
{
    const static unsigned int wysokoscWykresu = 28;
    const static unsigned int szerokoscWykresu = 120;
    const unsigned int pierwszyWyswietlanyKrok = std::max(0, (int)krokSymulacji - (int)szerokoscWykresu + 1);

    std::cout << "Wykres ilosci organizmow podczas ostatnich " << szerokoscWykresu << " krokow."
              << std::endl << std::endl;

    // najpierw szukamy najniższego i najwyższego punktu wykresu
    unsigned int min = statystyki.getIlosciGlonow()[pierwszyWyswietlanyKrok];
    unsigned int max = statystyki.getIlosciGlonow()[pierwszyWyswietlanyKrok];
    for (unsigned int i = pierwszyWyswietlanyKrok; i <= krokSymulacji; i++) {
        // glony
        if (statystyki.getIlosciGlonow()[i] > max) {
            max = statystyki.getIlosciGlonow()[i];
        } else if (statystyki.getIlosciGlonow()[i] < min) {
            min = statystyki.getIlosciGlonow()[i];
        }
        // grzyby
        if (statystyki.getIlosciGrzybow()[i] > max) {
            max = statystyki.getIlosciGrzybow()[i];
        } else if (statystyki.getIlosciGrzybow()[i] < min) {
            min = statystyki.getIlosciGrzybow()[i];
        }
        // bakterie
        if (statystyki.getIlosciBakterii()[i] > max) {
            max = statystyki.getIlosciBakterii()[i];
        } else if (statystyki.getIlosciBakterii()[i] < min) {
            min = statystyki.getIlosciBakterii()[i];
        }
    }

    // 1 wymiar jest dla każdego gatunku organizmu
    // (0 = glon, 1 = grzyb, 2 = bakteria),
    // 2 wymiar ma dla każdego kroku informację o tym,
    // w której linijce (od 0 do wysokoscWykresu-1)
    // znajduje się linia wykresu dla danego organizmu
    unsigned int tabliceLinii[3][szerokoscWykresu];

    for (unsigned int i = pierwszyWyswietlanyKrok; i <= krokSymulacji; i++) {
        tabliceLinii[0][i - pierwszyWyswietlanyKrok]
                = przekonwertujWartoscNaNrLinijkiWykresu(min, max, statystyki.getIlosciGlonow()[i], wysokoscWykresu);
        tabliceLinii[1][i - pierwszyWyswietlanyKrok]
                = przekonwertujWartoscNaNrLinijkiWykresu(min, max, statystyki.getIlosciGrzybow()[i], wysokoscWykresu);
        tabliceLinii[2][i - pierwszyWyswietlanyKrok]
                = przekonwertujWartoscNaNrLinijkiWykresu(min, max, statystyki.getIlosciBakterii()[i], wysokoscWykresu);
    }

    // teraz narysujemy każdą linijkę wykresu krok po kroku.
    // Jeśli tabliceLinii[organizm][krok] == linijka,
    // to na tej linijce znajduje się linia wykresu podczas tego kroku.
    for (int linijka = wysokoscWykresu; linijka >= 0; linijka--) {

        // wartości osi Y
        if (linijka == wysokoscWykresu) {
            std::cout << funkcjeUtility::liczbaBialeZnaki(max, 5, true) << "-|";
        } else if (linijka == 0) {
            std::cout << funkcjeUtility::liczbaBialeZnaki(min, 5, true) << "-|";
        } else if (linijka == wysokoscWykresu / 2) {
            std::cout << funkcjeUtility::liczbaBialeZnaki((max + min) / 2, 5, true) << "-|";
        } else {
            std::cout << funkcjeUtility::ilesBialychZnakow(6) << "|";
        }

        // rysowanie wykresu samo w sobie
        for (unsigned int krok = pierwszyWyswietlanyKrok; krok <= krokSymulacji; krok++) {
            bool wyswietlonoLinie = false;

            // idziemy od góry, aby linia bakterii była z przodu
            for (int organizm = 2; organizm >= 0; organizm--) {
                if (tabliceLinii[(unsigned int)organizm][krok - pierwszyWyswietlanyKrok] == (unsigned int)linijka) {
                    ustawKolorKonsoli(organizm);
                    std::cout << "O";
                    wyswietlonoLinie = true;
                    break;
                }
            }
            if (!wyswietlonoLinie) {
                std::cout << " ";
            }
        }
        std::cout << termcolor::reset << std::endl;
    }

    wyswietlInstrukcjeFunkcjiStatystycznych();
}

void Srodowisko::wyeksportujStatystykiWlasciwosci() const
{
    std::string tekst;
    const char nowaLinia = '\n', rozdzielnik = ',';

    std::string tablicaWlasciwosci[11] =
    {
        "Szerokość środowiska," + std::to_string(szerokosc) + rozdzielnik,
        "Wysokość środowiska," + std::to_string(wysokosc) + rozdzielnik,
        "Max wiek glonów," + std::to_string(maxWieki[0]) + rozdzielnik,
        "Max wiek grzybów," + std::to_string(maxWieki[1]) + rozdzielnik,
        "Max wiek bakterii," + std::to_string(maxWieki[2]) + rozdzielnik,
        "Max najedzenie glonów," + std::to_string(maxNajedzenia[0]) + rozdzielnik,
        "Max najedzenie grzybów," + std::to_string(maxNajedzenia[1]) + rozdzielnik,
        "Max najedzenie bakterii," + std::to_string(maxNajedzenia[2]) + rozdzielnik,
        "Koszt narodzin glonów," + std::to_string(kosztyNarodzin[0]) + rozdzielnik,
        "Koszt narodzin grzybów," + std::to_string(kosztyNarodzin[1]) + rozdzielnik,
        "Koszt narodzin bakterii," + std::to_string(kosztyNarodzin[2]) + rozdzielnik
    };

    tekst += "Właściwość,wartość właściwości,Krok,glonów,grzybów,bakterii,";
    tekst += "najedzonych glonów,najedzonych grzybów,najedzonych bakterii,";
    tekst += "rozmnożonych glonów,rozmnożonych grzybów,rozmnożonych bakterii,";
    tekst += nowaLinia;

    for (unsigned int krok = 0; krok <= krokSymulacji || krok < 11; krok++) {
        if (krok < 11) {
            tekst += tablicaWlasciwosci[krok];
        } else {
            tekst += ",,";
        }
        if (krok <= krokSymulacji) {
            tekst += std::to_string(krok) + ","
                + std::to_string(statystyki.getIlosciGlonow().at(krok)) + ","
                + std::to_string(statystyki.getIlosciGrzybow().at(krok)) + ","
                + std::to_string(statystyki.getIlosciBakterii().at(krok)) + ","
                + std::to_string((statystyki.getIlosciGlonow().at(krok)
                                  - statystyki.getIlosciRozmnozonychGlonow().at(krok))) + ","
                + std::to_string(statystyki.getIlosciNajedzonychGrzybow().at(krok)) + ","
                + std::to_string(statystyki.getIlosciNajedzonychBakterii().at(krok)) + ","
                + std::to_string(statystyki.getIlosciRozmnozonychGlonow().at(krok)) + ","
                + std::to_string(statystyki.getIlosciRozmnozonychGrzybow().at(krok)) + ","
                + std::to_string(statystyki.getIlosciRozmnozonychBakterii().at(krok));
        }
        tekst += nowaLinia;
    }

    std::cout << "Wygenerowano tekst do wyeksportowania." << std::endl
              << "Podaj nazwe pliku do zapisania." << std::endl;
    std::string nazwaPliku;
    while (true) {
        nazwaPliku = funkcjeUtility::dostanLinie();
        if (!funkcjeUtility::czyBezpiecznaNazwaPliku(nazwaPliku)) {
            std::cout << "Dozwolone sa wylacznie litery oraz cyfry," << std::endl
                      << "nazwa musi miec od 1 do 12 znakow." << std::endl;
        } else {
            break;
        }
    }
    nazwaPliku += ".csv";
    if (funkcjeUtility::sprobujZapisacTekstDoPliku(tekst, nazwaPliku)) {
        std::cout << "Pomyslnie wyeksportowano dane do pliku " << nazwaPliku << std::endl;
    } else {
        std::cout << termcolor::red << "Nie udalo sie wyeksportowac danych do pliku "
                  << nazwaPliku << std::endl;
    }
}

void Srodowisko::ustawKolorKonsoli(const unsigned int liczbaOrganizmu) const
{
    switch (liczbaOrganizmu)
    {
    case 0:
        termcolor::green(std::cout);
        break;
    case 1:
        termcolor::cyan(std::cout);
        break;
    case 2:
        termcolor::red(std::cout);
        break;
    case 3:
        termcolor::yellow(std::cout);
        break;
    }
}

unsigned int Srodowisko::przekonwertujWartoscNaNrLinijkiWykresu(const unsigned int min,
        const unsigned int max, const unsigned int wartosc, const unsigned int wysokoscWykresu) const
{
    double procentMiedzyMinMax = (wartosc - min) / ((double)max - min);
    return (unsigned int)(procentMiedzyMinMax * wysokoscWykresu);
}

std::string Srodowisko::dostanKolejnaInformacje(string *informacje, unsigned int *indeksInformacji)
{
    while (*indeksInformacji < szerokosc * wysokosc && informacje[*indeksInformacji].length() == 0) {
        (*indeksInformacji)++;
    }
    if (*indeksInformacji < szerokosc * wysokosc) {
        return "  |  " + informacje[(*indeksInformacji)++];
    } else {
        return "                                      ";
    }
}

void Srodowisko::wyswietlBoolUstawien(const bool zmienna, std::basic_ostream<char>& f(std::basic_ostream<char>&))
{
    if (zmienna) {
        std::cout << termcolor::cyan << "tak";
    } else {
        std::cout << termcolor::magenta << "nie";
    }
    if (f != nullptr) {
        f(std::cout);
    }
}

unsigned int Srodowisko::dostanNrOrganizmu(const char znakOrganizmu) const
{
    unsigned int nrOrganizmu = 3;
    switch (znakOrganizmu) {
    case Organizm::ZNAK_GLONU:
        nrOrganizmu = 0;
        break;
    case Organizm::ZNAK_GRZYBU:
        nrOrganizmu = 1;
        break;
    case Organizm::ZNAK_BAKTERII:
        nrOrganizmu = 2;
        break;
    }
    return nrOrganizmu;
}

bool Srodowisko::czyWyswietlacInfo(const char znakOrganizmu) const
{
    const unsigned int nr = dostanNrOrganizmu(znakOrganizmu);
    if (nr > 2) {
        return false;
    }
    return ustWyswietlania->wyswietlajInfo[nr];
}

bool Srodowisko::czySygnalizowacNajedzenie(const char znakOrganizmu) const
{
    const unsigned int nr = dostanNrOrganizmu(znakOrganizmu);
    if (nr > 2) {
        return false;
    }
    return ustWyswietlania->wyswietlajNajedzenie[nr];
}

bool Srodowisko::czySygnalizowacRozmnozenie(const char znakOrganizmu) const
{
    const unsigned int nr = dostanNrOrganizmu(znakOrganizmu);
    if (nr > 2) {
        return false;
    }
    return ustWyswietlania->wyswietlajRozmnozenie[nr];
}

bool Srodowisko::upewnijSieCzyOrganizmNadalIstnieje(const unsigned int i)
{
    // bakterie mogły zjeść inne organizmy żywe, więc trzeba upewniać się czy organizm jeszcze żyje
    Organizm* const organizm = zyweOrganizmy[i];
    if (zyweOrganizmy[i]->getCzyZostalWchloniety()) {
        delete organizm;
        zyweOrganizmy.erase(zyweOrganizmy.begin() + i);
        return false;
    }
    return true;
}

std::string* Srodowisko::informacjeOrganizmow() const
{
    string* const linie = new string[szerokosc * wysokosc];
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr || !czyWyswietlacInfo(nisze[i]->dostanZnak())) {
            linie[i] = "";
            continue;
        }
        const unsigned int x = dostanX(i);
        const unsigned int y = dostanY(i);
        const string litera(1, dostanLitereKolumny(x + 1));
        const string liczba = to_string(y + 1);
        string nazwa;
        switch (nisze[i]->dostanZnak()) {
        case Organizm::ZNAK_GLONU:
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
        const string wiek = (nisze[i]->getWiek() < 10 ? " " : "") + to_string(nisze[i]->getWiek());
        const string maxWiek = to_string(nisze[i]->getMaxWiek()) + (nisze[i]->getMaxWiek() < 10 ? " " : "");
        const string najedzenie = (nisze[i]->getNajedzenie() < 10 ? " " : "") + to_string(nisze[i]->getNajedzenie());
        const string maxNajedzenie = to_string(nisze[i]->getMaxNajedzenie()) + (nisze[i]->getMaxNajedzenie() < 10 ? " " : "");
        const string zmianaNajedzenia = nisze[i]->getWlasnieNajadl() ? "+" :
                                    nisze[i]->getWlasnieRozmnozyl() ? "-" : " ";
        linie[i] = (y + 1 < 10 ? " " : "") + litera + liczba + ": " + nazwa + " | "
                + wiek + "/" + maxWiek + " |   "
                + najedzenie + "/" + maxNajedzenie + zmianaNajedzenia + "  ";
    }
    return linie;
}

void Srodowisko::wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko)
{
    if (ustWyswietlania->nadrysowywanie && czyOstatnioDrukowanoSrodowisko) {
        funkcjeKonsoli::cofnijKursor(16 + wysokosc);
        std::cout << std::endl;
        // cout << "linia: " << linia << ", kolumna: " << kolumna << endl;
    }

    string* informacje = informacjeOrganizmow();
    // odpowiadajacy delete na koncu funkcji

    unsigned int indeksInformacji = 0;

    const unsigned int MARGINES = MAX_SZEROKOSC * 2;

    std::cout << " Ilosc krokow: " << funkcjeUtility::liczbaBialeZnaki(krokSymulacji, 7, false)
              << funkcjeUtility::ilesBialychZnakow(MARGINES - 20)
              << "  |  Poz: nazwa    |  wiek | najedzenie" << std::endl
              << " Ilosc glonow:   " << funkcjeUtility::liczbaBialeZnaki(iloscGlonow, 5, true)
              << funkcjeUtility::ilesBialychZnakow(MARGINES - 20)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl
              << " Ilosc grzybow:  " << funkcjeUtility::liczbaBialeZnaki(iloscGrzybow, 5, true)
              << funkcjeUtility::ilesBialychZnakow(MARGINES - 20)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl
              << " Ilosc bakterii: " << funkcjeUtility::liczbaBialeZnaki(iloscBakterii, 5, true)
              << funkcjeUtility::ilesBialychZnakow(MARGINES - 20)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl
              << " Ilosc martwych: " << funkcjeUtility::liczbaBialeZnaki(iloscMartwych, 5, true)
              << funkcjeUtility::ilesBialychZnakow(MARGINES - 20)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl
              << "Wyswietlanie srodowiska    " << funkcjeUtility::ilesBialychZnakow(MARGINES - 25)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl
              << "                 " << funkcjeUtility::ilesBialychZnakow(MARGINES - 15)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl;

    for (unsigned int i = 1; i <= szerokosc; i++) {
        if (i == 1) {
            std::cout << "   ";
        }
        std::cout << dostanLitereKolumny(i) << (i == szerokosc ? "" : " ");
    }

    std::cout << funkcjeUtility::ilesBialychZnakow(MARGINES - szerokosc * 2)
              << dostanKolejnaInformacje(informacje, &indeksInformacji) << std::endl;
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
        std::cout << funkcjeUtility::ilesBialychZnakow(MARGINES - szerokosc * 2)
                  << dostanKolejnaInformacje(informacje, &indeksInformacji);
        std::cout << std::endl;
    }
    delete [] informacje;
}

void Srodowisko::petla()
{
    std::cin.clear();
    string wejscie = "";
    bool pierwszeWejscie = true;
    bool ostatnioDrukowanoSrodowisko = false;
    while (wejscie != "E") {
        std::cout << "Enter bez znakow - wykonanie kroku symulacji i wyswietlenie srodowiska"
                  << std::endl << "b - wyswietlenie srodowiska"
                  << std::endl << "s - statystyki"
                  << std::endl << "u - ustawienia"
                  << std::endl << "e - opuszczenie srodowiska"
                  << std::endl;

        wejscie = pierwszeWejscie ? "B" : funkcjeUtility::dostanLinie();
        pierwszeWejscie = false;

        // zamiana wejścia na duże litery
        for (auto & c: wejscie) {
            c = std::toupper(c);
        }

        if (wejscie == "") {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::krokOrazWyswietlanieSrodowiska;
        } else if (wejscie == "B") {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::wyswietlanieSrodowiska;
        } else if (wejscie == "SE") {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::zaden;
            wyeksportujStatystykiWlasciwosci();
        } else if (wejscie.length() > 0 && wejscie[0] == 'S') {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::wyswietlanieStatystyk;
        } else if (wejscie == "U") {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::wyswietlanieUstawien;
        } else if (wejscie == "E") {
            return;
        } else if (wejscie == "W") {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::wyswietlanieWykresu;
        } else if (wejscie == "N") {
            funkcjeUtility::przelaczBool(&ustWyswietlania->nadrysowywanie);
        } else if (wejscie.length() == 2 && wejscie[1] >= '0' && wejscie[1] <= '2') {
            switch (wejscie[0]) {
            case 'J':
                funkcjeUtility::przelaczBool(&ustWyswietlania->wyswietlajNajedzenie[(unsigned int)(wejscie[1] - '0')]);
                break;
            case 'R':
                funkcjeUtility::przelaczBool(&ustWyswietlania->wyswietlajRozmnozenie[(unsigned int)(wejscie[1] - '0')]);
                break;
            case 'I':
                funkcjeUtility::przelaczBool(&ustWyswietlania->wyswietlajInfo[(unsigned int)(wejscie[1] - '0')]);
                break;
            }
        } else {
            ustWyswietlania->obecnyTryb = ustawieniaWyswietlania::trybWyswietlania::zaden;
        }

        // Rysujemy horyzontalną linię tylko jeśli środowisko nie będzie nadrysowane
        if (!(ostatnioDrukowanoSrodowisko && (ustWyswietlania->obecnyTryb
              == ustawieniaWyswietlania::trybWyswietlania::krokOrazWyswietlanieSrodowiska
                                              || ustWyswietlania->obecnyTryb
              == ustawieniaWyswietlania::trybWyswietlania::wyswietlanieSrodowiska))) {
            std::cout << std::endl << "-----------------------" << std::endl;
        }

        switch (ustWyswietlania->obecnyTryb) {
        case ustawieniaWyswietlania::trybWyswietlania::krokOrazWyswietlanieSrodowiska:
            wykonajKrokSymulacji();
            wyswietlSrodowisko(ostatnioDrukowanoSrodowisko);
            break;
        case ustawieniaWyswietlania::trybWyswietlania::wyswietlanieSrodowiska:
            wyswietlSrodowisko(ostatnioDrukowanoSrodowisko);
            break;
        case ustawieniaWyswietlania::trybWyswietlania::wyswietlanieStatystyk:
            if (wejscie.length() > 1) {
                bool moznaPrzekonwertowacNaLiczbe = true;
                for (unsigned int i = 1; i < wejscie.length(); i++) {
                    if (!std::isdigit(wejscie[i])) {
                        moznaPrzekonwertowacNaLiczbe = false;
                    }
                }
                if (moznaPrzekonwertowacNaLiczbe) {
                    wyswietlStatystyki(std::stoi(wejscie.substr(1, wejscie.length() - 1)));
                } else {
                    std::cout << "Nie rozpoznano parametru jako liczby" << std::endl;
                }
            } else {
                wyswietlStatystyki();
            }
            break;
        case ustawieniaWyswietlania::wyswietlanieWykresu:
            wyswietlWykresIlosciOrganizmow();
            break;
        case ustawieniaWyswietlania::trybWyswietlania::wyswietlanieUstawien:
            wyswietlUstawienia();
            break;
        case ustawieniaWyswietlania::trybWyswietlania::zaden:
            break;
        }
        ostatnioDrukowanoSrodowisko = ustWyswietlania->obecnyTryb <= 1;
    }
}

Srodowisko::~Srodowisko()
{
    for (unsigned int i = 0; i < szerokosc * wysokosc; i++) {

        // polecenie delete samo wykonuje sprawdzenie, czy
        // usuwany wskaźnik nie wynosi nullptr,
        // więc bez sensu byłoby jeszcze raz tutaj to sprawdzać
        delete nisze[i];
    }
    delete [] nisze;
}

void Srodowisko::wykonajKrokSymulacji()
{
    Organizm* obecnyOrganizm;

    // udostępnianie organizmom informacji o otoczeniu oraz zgromadzenie
    // informacji o żywych organizmach do przyspieszenia iteracji czynności życiowych
    zyweOrganizmy.clear();
    for (unsigned int i = 0; i < wysokosc * szerokosc; i++) {
        if (nisze[i] == nullptr || !nisze[i]->czyZywy()) {
            continue;
        }

        zyweOrganizmy.push_back(nisze[i]);

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
    for (unsigned int i = 0; i < zyweOrganizmy.size(); i++) {
        obecnyOrganizm = zyweOrganizmy[i];
        if (obecnyOrganizm->czyZywy() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeSprobujRozmnozycSie();
        }
    }

    // wywołanie możliwych prób najedzenia się u organizmów
    for (unsigned int i = 0; i < zyweOrganizmy.size(); i++) {
        if (!upewnijSieCzyOrganizmNadalIstnieje(i)) {
            i--;
            continue;
        }
        obecnyOrganizm = zyweOrganizmy[i];
        if (obecnyOrganizm->czyZywy() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeSprobujNajescSie();
        }
    }

    // wywołanie starzenia się u organizmów
    // na tym kroku zwalniamy też miejsce zajmowane
    // przez wchłonięte żywe organizmy poprzez sprawdzenie czy nadal istnieją
    for (unsigned int i = 0; i < zyweOrganizmy.size(); i++) {
        if (!upewnijSieCzyOrganizmNadalIstnieje(i)) {
            i--;
            continue;
        }
        obecnyOrganizm = zyweOrganizmy[i];
        obecnyOrganizm->starzenieSie();
    }

    // wywołanie możliwych prób poruszenia się u organizmów
    for (unsigned int i = 0; i < zyweOrganizmy.size(); i++) {
        obecnyOrganizm = zyweOrganizmy[i];
        if (obecnyOrganizm->czyZywy() && obecnyOrganizm->getWiek() != obecnyOrganizm->getMaxWiek()) {
            obecnyOrganizm->mozeSprobujPoruszycSie();
        }
    }

    krokSymulacji++;

    podliczIlosciOrganizmow();
    statystyki.dodajStatystykiOstatniegoKroku(this);
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

unsigned int Srodowisko::dostanX(const unsigned int indeksNiszy) const
{
    return indeksNiszy % szerokosc;
}

unsigned int Srodowisko::dostanY(const unsigned int indeksNiszy) const
{
    return indeksNiszy / szerokosc;
}

unsigned int Srodowisko::indeksNiszyOdKoordynat(const unsigned int x, const unsigned int y) const
{
    return (y * szerokosc) + x;
}

unsigned int Srodowisko::dostanIndeksSasiada( unsigned int x, unsigned int y, unsigned int nrSasiada) const
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
    return indeksNiszyOdKoordynat(x, y);
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciGlonow() const
{
    return ilosciGlonow;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciRozmnozonychBakterii() const
{
    return ilosciRozmnozonychBakterii;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciRozmnozonychGrzybow() const
{
    return ilosciRozmnozonychGrzybow;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciRozmnozonychGlonow() const
{
    return ilosciRozmnozonychGlonow;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciNajedzonychBakterii() const
{
    return ilosciNajedzonychBakterii;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciNajedzonychGrzybow() const
{
    return ilosciNajedzonychGrzybow;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciMartwych() const
{
    return ilosciMartwych;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciBakterii() const
{
    return ilosciBakterii;
}

const std::vector<unsigned int> &Srodowisko::statystykiSrodowiska::getIlosciGrzybow() const
{
    return ilosciGrzybow;
}

void Srodowisko::statystykiSrodowiska::dodajStatystykiOstatniegoKroku(Srodowisko * const srodowisko)
{
    ilosciGlonow.push_back(srodowisko->iloscGlonow);
    ilosciGrzybow.push_back(srodowisko->iloscGrzybow);
    ilosciBakterii.push_back(srodowisko->iloscBakterii);
    ilosciNajedzonychGrzybow.push_back(0);
    ilosciNajedzonychBakterii.push_back(0);
    ilosciRozmnozonychGlonow.push_back(0);
    ilosciRozmnozonychGrzybow.push_back(0);
    ilosciRozmnozonychBakterii.push_back(0);

    Organizm *organizm;
    for (unsigned int i = 0; i < srodowisko->szerokosc * srodowisko->wysokosc; i++) {
        organizm = srodowisko->nisze[i];
        if (organizm == nullptr) {
            // w tej niszy nie ma organizmu
            continue;
        }
        switch (organizm->dostanZnak())
        {
        case Organizm::ZNAK_GLONU:
            if (organizm->getWlasnieRozmnozyl()) {
                ilosciRozmnozonychGlonow.back()++;
            }
            break;
        case Organizm::ZNAK_GRZYBU:
            if (organizm->getWlasnieNajadl()) {
                ilosciNajedzonychGrzybow.back()++;
            }
            if (organizm->getWlasnieRozmnozyl()) {
                ilosciRozmnozonychGrzybow.back()++;
            }
            break;
        case Organizm::ZNAK_BAKTERII:
            if (organizm->getWlasnieNajadl()) {
                ilosciNajedzonychBakterii.back()++;
            }
            if (organizm->getWlasnieRozmnozyl()) {
                ilosciRozmnozonychBakterii.back()++;
            }
            break;
        }
    }
}
