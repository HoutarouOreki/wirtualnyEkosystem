#include "organizm.h"
#include "glon.h"
#include "funkcjeUtility.h"

Organizm::Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, const unsigned int poczatkowyWiek)
{
    this->maxWiek = maxWiek;
    this->maxNajedzenie = maxNajedzenie;
    this->kosztNarodzin = kosztNarodzin;
    najedzenie = 0;
    wiek = poczatkowyWiek;
    czyZostalWchloniety = false;
}

Organizm::~Organizm()
{
}

bool Organizm::czyZywy() const
{
    return wiek <= maxWiek;
}

bool Organizm::czyPrzejedzony() const
{
    return najedzenie >= maxNajedzenie;
}

bool Organizm::czyNajedzony() const
{
    return najedzenie >= kosztNarodzin;
}

bool Organizm::getWlasnieNajadl() const
{
    return czyZywy() ? czyWlasnieNajadl : false;
}

bool Organizm::getWlasnieRozmnozyl() const
{
    return czyZywy() ? czyWlasnieRozmnozyl : false;
}


char Organizm::znak() const
{
    return '?';
}

char Organizm::dostanZnak() const
{
    if (czyZywy()) {
        return znak();
    } else {
        return ZNAK_MARTWEGO;
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

void Organizm::zobaczSrodowisko(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy)
{
    this->nisze = nisze;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
        this->pozycjeSasiednichNiszy[i] = pozycjeSasiednichNiszy[i];
    }
    this->iloscSasiednichNiszy = nSasiednichNiszy;
}

void Organizm::mozeSprobujRozmnozycSie()
{
    czyWlasnieRozmnozyl = false;
    if (czyNajedzony()) {
        if (probaRozmnozeniaSie()) {
            czyWlasnieRozmnozyl = true;
        }
    }
}

bool Organizm::getCzyZostalWchloniety() const
{
    return czyZostalWchloniety;
}

Organizm **Organizm::getNisze() const
{
    return nisze;
}

unsigned int *Organizm::getPozycjeSasiednichNiszy()
{
    return pozycjeSasiednichNiszy;
}

unsigned int Organizm::getIloscSasiednichNiszy() const
{
    return iloscSasiednichNiszy;
}

bool Organizm::probaRozmnozeniaSie()
{
    unsigned int zajeteNisze = 0;
    for (unsigned int i = 0; i < iloscSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] != nullptr) {
            zajeteNisze++;
        }
    }

    // jeśli każda nisza w sąsiedztwie jest zajęta, to nie można się rozmnożyć
    if (zajeteNisze == iloscSasiednichNiszy) {
        return false;
    }

    // w tym miejscu wiemy, że na pewno istnieje wolna nisza dla potomka
    // losujemy dla niego sąsiednią niszę dopóki nie znajdziemy jakiejś wolnej
    int wylosowanySasiad = funkcjeUtility::wylosujInt(0, iloscSasiednichNiszy - 1);
    while (nisze[pozycjeSasiednichNiszy[wylosowanySasiad]] != nullptr) {
        wylosowanySasiad = funkcjeUtility::wylosujInt(0, iloscSasiednichNiszy - 1);
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
    czyWlasnieNajadl = false;
    if (!czyPrzejedzony() && !getWlasnieRozmnozyl()) {
        if (probaNajedzeniaSie()) {
            najedzenie++;
            czyWlasnieNajadl = true;
        }
    }
}

bool Organizm::probaNajedzeniaSie()
{
    return false;
}

void Organizm::mozeSprobujPoruszycSie()
{
    if (!getWlasnieNajadl() && !getWlasnieRozmnozyl()) {
        probaPoruszeniaSie();
    }
}

void Organizm::probaPoruszeniaSie()
{
}

void Organizm::wchlonOrganizm(unsigned int nrNiszy)
{
    if (nisze[nrNiszy]->czyZywy()) {
        // jeśli żyje, to jest w tablicy żywych organizmów w środowisku
        // i tam powinien zostać usunięty
        nisze[nrNiszy]->czyZostalWchloniety = true;
    } else {
        delete nisze[nrNiszy];
    }
    nisze[nrNiszy] = nullptr;
}

void Organizm::wchlonOrazZajmijPozycjeOrganizmu(unsigned int nrNiszy)
{
    wchlonOrganizm(nrNiszy);
    nisze[wlasnyIndeks] = nullptr;
    nisze[nrNiszy] = this;
}

void Organizm::sprobujPrzemiescicSie()
{
    bool czyMoznaSiePrzemiescic = false;
    for (unsigned int i = 0; i < iloscSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] == nullptr) {
            czyMoznaSiePrzemiescic = true;
            break;
        }
    }
    if (!czyMoznaSiePrzemiescic) {
        return;
    }
    int wylosowanaNisza;
    nisze[wlasnyIndeks] = nullptr;
    do {
        wylosowanaNisza = funkcjeUtility::wylosujInt(0, iloscSasiednichNiszy - 1);
    } while (nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] != nullptr);
    nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] = this;
    wlasnyIndeks = pozycjeSasiednichNiszy[wylosowanaNisza];
}

Organizm* Organizm::wygenerujDziecko()
{
    return nullptr;
}
