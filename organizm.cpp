#include "organizm.h"
#include "glon.h"
#include "funkcjeUtility.h"

unsigned int Organizm::getWiek() const
{
    return wiek;
}

unsigned int Organizm::getNajedzenie() const
{
    return najedzenie;
}

bool Organizm::bCzyZyje() const
{
    return wiek <= maxWiek;
}

bool Organizm::bCzyNajedzony() const
{
    return najedzenie >= maxNajedzenie;
}

Organizm::Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin)
{
    this->maxWiek = maxWiek;
    this->maxNajedzenie = maxNajedzenie;
    this->kosztNarodzin = kosztNarodzin;
    najedzenie = 0;
    wiek = 0;
}

Organizm::~Organizm()
{
}

void Organizm::krokSymulacji(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow)
{
    wiek++;
    if (!bCzyZyje()) {
        return;
    }
    bool czyJadl = false, wynikRozmn = false;
    if (!bCzyNajedzony()) { // nienajedzony — szuka jedzenia
        czyJadl = bProbaNajedzeniaSie(nisze, pozycjeSasiadow, nSasiadow);
        if (czyJadl) {
            najedzenie++;
        }
    } else { // najedzony — probuje sie rozmnozyc
        wynikRozmn = bProbaRozmnozeniaSie(nisze, pozycjeSasiadow, nSasiadow);
    }
    koniecKroku(czyJadl, wynikRozmn, nisze, pozycjeSasiadow, nSasiadow);
}

bool Organizm::bProbaRozmnozeniaSie(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow)
{
    int zajeteNisze = 0;
    for (int i = 0; i < nSasiadow; i++)
    {
        if (nisze[pozycjeSasiadow[i]] != nullptr)
        {
            zajeteNisze++;
        }
    }
    if (zajeteNisze == nSasiadow)
    {
        return false;
    }

    int wylosowanySasiad = funkcjeUtility::wylosujInt(0, nSasiadow - 1);
    while (nisze[pozycjeSasiadow[wylosowanySasiad]] != nullptr)
    {
        wylosowanySasiad = funkcjeUtility::wylosujInt(0, nSasiadow - 1);
    }
    nisze[pozycjeSasiadow[wylosowanySasiad]] = wygenerujDziecko();
    najedzenie -= kosztNarodzin;
    return true;
}

unsigned int Organizm::getMaxWiek() const
{
    return maxWiek;
}

unsigned int Organizm::getMaxNajedzenie() const
{
    return maxNajedzenie;
}

bool Organizm::bProbaNajedzeniaSie(Organizm**, int[], int)
{
    return false;
}

void Organizm::koniecKroku(bool, bool, Organizm**, int[], int) {}

char Organizm::znak() const
{
    return '?';
}

char Organizm::dostanZnak() const
{
    if (bCzyZyje()) {
        return znak();
    } else {
        return '+';
    }
}

Organizm* Organizm::wygenerujDziecko()
{
    return nullptr;
}
