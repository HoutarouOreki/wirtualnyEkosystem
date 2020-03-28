#include <iostream>
#include "bakteria.h"
#include "funkcjeUtility.h"

bool Bakteria::probaNajedzeniaSieOrganizmem(char znakOrganizmu)
{
    // najpierw szuka organizmu w sąsiedztwie
    bool znalezionoOrganizm = false;
    for (unsigned int i = 0; i < getIloscSasiednichNiszy(); i++) {
        if (getNisze()[getPozycjeSasiednichNiszy()[i]] != nullptr
                && getNisze()[getPozycjeSasiednichNiszy()[i]]->dostanZnak() == znakOrganizmu) {
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
            wylosowanyOrganizm = funkcjeUtility::wylosujInt(0, getIloscSasiednichNiszy() - 1);
        } while (getNisze()[getPozycjeSasiednichNiszy()[wylosowanyOrganizm]] == nullptr ||
                 getNisze()[getPozycjeSasiednichNiszy()[wylosowanyOrganizm]]->dostanZnak() != znakOrganizmu);

        wchlonOrazZajmijPozycjeOrganizmu(getPozycjeSasiednichNiszy()[wylosowanyOrganizm]);
        return true;
    }

    // w tym miejscu próba najedzenia się tym typem organizmu nie powiodła się
    return false;
}

bool Bakteria::probaNajedzeniaSie()
{
    // najpierw próbuje znaleźć i zjeść glon
    if (probaNajedzeniaSieOrganizmem(ZNAK_GLONU)) {
        return true;
    }

    // jeśli nie znaleziono żadnego glonu, to próbuje
    // wykonać to samo działanie, ale na bakteriach
    if (probaNajedzeniaSieOrganizmem(ZNAK_BAKTERII)) {
        return true;
    }

    // w tym miejscu próby najedzenia się nie powiodły się
    return false;
}

void Bakteria::probaPoruszeniaSie()
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
