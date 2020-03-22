#include "organizm.h"
#include "glon.h"
#include "funkcjeUtility.h"

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

bool Organizm::bCzyZyje() const
{
    return wiek <= maxWiek;
}

bool Organizm::bCzyNajedzony() const
{
    return najedzenie >= maxNajedzenie;
}

bool Organizm::getWlasnieNajadl() const
{
    return bCzyZyje() ? bWlasnieNajadl : false;
}

bool Organizm::getWlasnieRozmnozyl() const
{
    return bCzyZyje() ? bWlasnieRozmnozyl : false;
}


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

unsigned int Organizm::getWiek() const
{
    return wiek;
}

unsigned int Organizm::getMaxWiek() const
{
    return maxWiek;
}

unsigned int Organizm::getNajedzenie() const
{
    return najedzenie;
}

unsigned int Organizm::getMaxNajedzenie() const
{
    return maxNajedzenie;
}

void Organizm::zobaczSrodowisko(Organizm **nisze, int *pozycjeSasiednichNiszy, int nSasiednichNiszy)
{
    this->nisze = nisze;
    for (int i = 0; i < nSasiednichNiszy; i++) {
        this->pozycjeSasiednichNiszy[i] = pozycjeSasiednichNiszy[i];
    }
    this->nSasiednichNiszy = nSasiednichNiszy;
}

void Organizm::mozeRozmnozSie()
{
    bWlasnieRozmnozyl = false;
    if (bCzyNajedzony()) {
        if (probaRozmnozeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy)) {
            bWlasnieRozmnozyl = true;
        }
    }
}

bool Organizm::probaRozmnozeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy)
{
    int zajeteNisze = 0;
    for (int i = 0; i < nSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] != nullptr) {
            zajeteNisze++;
        }
    }

    // jeśli każda nisza w sąsiedztwie jest zajęta, to nie można się rozmnożyć
    if (zajeteNisze == nSasiednichNiszy) {
        return false;
    }

    // w tym miejscu wiemy, że na pewno istnieje wolna nisza dla potomka
    // losujemy dla niego sąsiednią niszę dopóki nie znajdziemy jakiejś wolnej
    int wylosowanySasiad = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
    while (nisze[pozycjeSasiednichNiszy[wylosowanySasiad]] != nullptr) {
        wylosowanySasiad = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
    }

    // umieszczamy nowego potomka w wylosowanej niszy
    nisze[pozycjeSasiednichNiszy[wylosowanySasiad]] = wygenerujDziecko();

    // narodziny potomka kosztują punkty najedzenia
    najedzenie -= kosztNarodzin;

    return true;
}

void Organizm::starzenieSie()
{
    wiek++;
}

void Organizm::mozeSprobujNajescSie()
{
    bWlasnieNajadl = false;
    if (!bCzyNajedzony() && !getWlasnieRozmnozyl()) {
        if (probaNajedzeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy)) {
            najedzenie++;
            bWlasnieNajadl = true;
        }
    }
}

bool Organizm::probaNajedzeniaSie(Organizm**, int[], int)
{
    return false;
}

void Organizm::mozeSprobujPoruszycSie()
{
    if (!getWlasnieNajadl() && !getWlasnieRozmnozyl()) {
        probaPoruszeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy);
    }
}

void Organizm::probaPoruszeniaSie(Organizm **, int *, int)
{
}

Organizm* Organizm::wygenerujDziecko()
{
    return nullptr;
}
