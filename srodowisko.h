#include <string>
#include <vector>
#include "organizm.h"
#ifndef SRODOWISKO_H
#define SRODOWISKO_H

class Srodowisko
{
private:
    unsigned int szerokosc;
    unsigned int wysokosc;
    unsigned int krokSymulacji;

    unsigned int iloscGlonow;
    unsigned int iloscGrzybow;
    unsigned int iloscBakterii;
    unsigned int iloscMartwych;
    void podliczIlosciOrganizmow();

    unsigned int dostanIndeks(unsigned int x, unsigned int y) const;
    Organizm* getNisza(unsigned int x, unsigned int y) const;
    void setNisza(Organizm* organizm, unsigned int x, unsigned int y);
    unsigned int dostanX(int indeksNiszy) const;
    unsigned int dostanY(int indeksNiszy) const;
    unsigned int dostanIndeksSasiada(unsigned int x, unsigned int y, unsigned int nrSasiada) const;

    std::string* informacjeOrganizmow() const;
    std::vector<unsigned int> pozycjeZywychOrganizmow;
    bool upewnijSieCzyOrganizmNadalIstnieje(int i);

    void wyswietlUstawienia();

    // preferencje wyświetlania
    unsigned int obecnyTryb;
    bool wyswietlajNajedzenie[3];
    bool wyswietlajRozmnozenie[3];
    bool wyswietlajInfo[3];
    void wyswietlBoolUstawien(bool zmienna, std::basic_ostream<char>& f(std::basic_ostream<char>&));
    bool czyWyswietlacInfo(char znakOrganizmu) const;
    bool czySygnalizowacNajedzenie(char znakOrganizmu) const;
    bool czySygnalizowacRozmnozenie(char znakOrganizmu) const;
public:
    Srodowisko();
    ~Srodowisko();

    void wykonajKrokSymulacji();

    Organizm** nisze;

    unsigned int getSzerokosc() const;

    unsigned int getWysokosc() const;

    unsigned int maxWiekGlonow;
    unsigned int maxWiekGrzybow;
    unsigned int maxWiekBakterii;

    unsigned int maxNajedzenieGlonow;
    unsigned int maxNajedzenieGrzybow;
    unsigned int maxNajedzenieBakterii;

    unsigned int kosztNarodzinGlonow;
    unsigned int kosztNarodzinGrzybow;
    unsigned int kosztNarodzinBakterii;

    void wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko);
    void petla();
};

#endif // SRODOWISKO_H
