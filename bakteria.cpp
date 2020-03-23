#include "bakteria.h"
#include "funkcjeUtility.h"

bool Bakteria::probaNajedzeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy)
{
    // najpierw szuka w sąsiedztwie glonów
    bool znalezionoOrganizm = false;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] != nullptr
                && nisze[pozycjeSasiednichNiszy[i]]->dostanZnak() == ZNAK_GLONU) {
            znalezionoOrganizm = true;
            break;
        }
    }

    // jeśli w sąsiedztwie istnieją glony, to
    // wybiera losowo jeden i go wchłania najadając się
    if (znalezionoOrganizm) {
        unsigned int wylosowanyGlon;
        do {
            wylosowanyGlon = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
        } while (nisze[pozycjeSasiednichNiszy[wylosowanyGlon]] == nullptr ||
                 nisze[pozycjeSasiednichNiszy[wylosowanyGlon]]->dostanZnak() != ZNAK_GLONU);
        wchlonOrganizm(pozycjeSasiednichNiszy[wylosowanyGlon]);
        return true;
    }

    // jeśli nie znaleziono żadnego glonu, to próbuje
    // wykonać to samo działanie, ale na bakteriach
    znalezionoOrganizm = false;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] != nullptr
                && nisze[pozycjeSasiednichNiszy[i]]->dostanZnak() == ZNAK_BAKTERII) {
            znalezionoOrganizm = true;
            break;
        }
    }

    if (znalezionoOrganizm) {
        unsigned int wylosowanaBakteria;
        do {
            wylosowanaBakteria = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
        } while (nisze[pozycjeSasiednichNiszy[wylosowanaBakteria]] == nullptr ||
                 nisze[pozycjeSasiednichNiszy[wylosowanaBakteria]]->dostanZnak() != ZNAK_BAKTERII);
        wchlonOrganizm(pozycjeSasiednichNiszy[wylosowanaBakteria]);
        return true;
    }

    // w tym miejscu próby najedzenia się nie powiodły się
    return false;
}

void Bakteria::probaPoruszeniaSie(Organizm **, unsigned int *, unsigned int)
{
    sprobujPrzemiescicSie();
}

Bakteria::Bakteria(const unsigned int maxWiek, const unsigned int maxNajedzenie, const unsigned int kosztNarodzin)
    : Organizm(maxWiek, maxNajedzenie, kosztNarodzin)
{
}

char Bakteria::znak() const
{
    return Organizm::ZNAK_BAKTERII;
}

Organizm *Bakteria::wygenerujDziecko()
{
    return new Bakteria(maxWiek, maxNajedzenie, kosztNarodzin);
}
