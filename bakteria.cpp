#include <iostream>
#include "bakteria.h"
#include "funkcjeUtility.h"

bool Bakteria::probaNajedzeniaSieOrganizmem(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy, char znakOrganizmu)
{
    // najpierw szuka organizmu w sąsiedztwie
    bool znalezionoOrganizm = false;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] != nullptr
                && nisze[pozycjeSasiednichNiszy[i]]->dostanZnak() == znakOrganizmu) {
            znalezionoOrganizm = true;
            break;
        }
    }

    // jeśli w sąsiedztwie istnieją takie organizmy, to
    // wybiera losowo jeden i go wchłania najadając się
    // oraz zajmuje jego miejsce
    if (znalezionoOrganizm) {
        unsigned int wylosowanyOrganizm;
        do {
            wylosowanyOrganizm = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
        } while (nisze[pozycjeSasiednichNiszy[wylosowanyOrganizm]] == nullptr ||
                 nisze[pozycjeSasiednichNiszy[wylosowanyOrganizm]]->dostanZnak() != znakOrganizmu);

        wchlonOrazZajmijPozycjeOrganizmu(pozycjeSasiednichNiszy[wylosowanyOrganizm]);
        return true;
    }

    // w tym miejscu próba najedzenia się tym typem organizmu nie powiodła się
    return false;
}

bool Bakteria::probaNajedzeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy)
{
    // najpierw próbuje znaleźć i zjeść glon
    if (probaNajedzeniaSieOrganizmem(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy, ZNAK_GLONU)) {
        return true;
    }

    // jeśli nie znaleziono żadnego glonu, to próbuje
    // wykonać to samo działanie, ale na bakteriach
    if (probaNajedzeniaSieOrganizmem(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy, ZNAK_BAKTERII)) {
        return true;
    }

    // w tym miejscu próby najedzenia się nie powiodły się
    return false;
}

void Bakteria::probaPoruszeniaSie(Organizm **, unsigned int *, unsigned int)
{
    sprobujPrzemiescicSie();
}

Bakteria::Bakteria(const unsigned int maxWiek, const unsigned int maxNajedzenie, const unsigned int kosztNarodzin, const unsigned int poczatkowyWiek)
    : Organizm(maxWiek, maxNajedzenie, kosztNarodzin, poczatkowyWiek)
{
}

char Bakteria::znak() const
{
    return Organizm::ZNAK_BAKTERII;
}

Organizm *Bakteria::wygenerujDziecko()
{
    return new Bakteria(maxWiek, maxNajedzenie, kosztNarodzin);
    // odpowiadajacy delete wewnatrz Organizm::wchlonOrganizm
    // oraz Srodowisko::~Srodowisko
}
