#include <string>
#include "organizm.h"
#ifndef SRODOWISKO_H
#define SRODOWISKO_H

class Srodowisko
{
private:
    unsigned int szerokosc;
    unsigned int wysokosc;
    unsigned int krokSymulacji;
    unsigned int dostanIndeks(unsigned int x, unsigned int y) const;
    Organizm* getNisza(unsigned int x, unsigned int y) const;
    void setNisza(Organizm* organizm, unsigned int x, unsigned int y);
    unsigned int dostanX(int indeksNiszy) const;
    unsigned int dostanY(int indeksNiszy) const;
    unsigned int dostanIndeksSasiada(unsigned int x, unsigned int y, unsigned int nrSasiada) const;
    std::string* informacjeOrganizmow() const;
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

    void wyswietlSrodowisko();

    void rozpocznijPetle();
};

#endif // SRODOWISKO_H
