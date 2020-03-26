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
    bZostalWchloniety = false;
}

Organizm::~Organizm()
{
}

bool Organizm::bCzyZyje() const
{
    return wiek <= maxWiek;
}

bool Organizm::bCzyPrzejedzony() const
{
    return najedzenie >= maxNajedzenie;
}

bool Organizm::bCzyNajedzony() const
{
    return najedzenie >= kosztNarodzin;
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
    this->nSasiednichNiszy = nSasiednichNiszy;
}

void Organizm::mozeSprobujRozmnozycSie()
{
    bWlasnieRozmnozyl = false;
    if (bCzyNajedzony()) {
        if (probaRozmnozeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy)) {
            bWlasnieRozmnozyl = true;
        }
    }
}

bool Organizm::getZostalWchloniety() const
{
    return bZostalWchloniety;
}

bool Organizm::probaRozmnozeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy)
{
    unsigned int zajeteNisze = 0;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
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
    if (!bCzyPrzejedzony() && !getWlasnieRozmnozyl()) {
        if (probaNajedzeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy)) {
            najedzenie++;
            bWlasnieNajadl = true;
        }
    }
}

bool Organizm::probaNajedzeniaSie(Organizm**, unsigned int*, unsigned int)
{
    return false;
}

void Organizm::mozeSprobujPoruszycSie()
{
    if (!getWlasnieNajadl() && !getWlasnieRozmnozyl()) {
        probaPoruszeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy);
    }
}

void Organizm::probaPoruszeniaSie(Organizm **, unsigned int*, unsigned int)
{
}

void Organizm::wchlonOrganizm(unsigned int nrNiszy)
{
    if (nisze[nrNiszy]->bCzyZyje()) {
        // jeśli żyje, to jest w tablicy żywych organizmów w środowisku
        // i tam powinien zostać usunięty
        nisze[nrNiszy]->bZostalWchloniety = true;
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
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
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
        wylosowanaNisza = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
    } while (nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] != nullptr);
    nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] = this;
    wlasnyIndeks = pozycjeSasiednichNiszy[wylosowanaNisza];
}

Organizm* Organizm::wygenerujDziecko()
{
    return nullptr;
}
