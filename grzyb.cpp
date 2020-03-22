#include "grzyb.h"
#include "funkcjeUtility.h"

Grzyb::Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin) : Organizm(maxWiek, maxNajedzenie, kosztNarodzin)
{

}

Organizm* Grzyb::wygenerujDziecko()
{
    return new Grzyb(maxWiek, maxNajedzenie, kosztNarodzin);
}

void Grzyb::probaPoruszeniaSie(Organizm **nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy)
{
    bool czyMoznaSiePrzemiescic = false;
    for (int i = 0; i < nSasiednichNiszy; i++) {
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
    Organizm::probaPoruszeniaSie(nisze, pozycjeSasiednichNiszy, nSasiednichNiszy);
}

bool Grzyb::probaNajedzeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy)
{
    Organizm* sasiad;
    bool istniejeMartwySasiad = false;
    for (int i = 0; i < nSasiednichNiszy; i++) {
        if (nisze[pozycjeSasiednichNiszy[i]] == nullptr) {
            continue;
        }
        sasiad = nisze[pozycjeSasiednichNiszy[i]];
        if (!sasiad->bCzyZyje()) {
            istniejeMartwySasiad = true;
            break;
        }
    }
    if (!istniejeMartwySasiad) {
        return false;
    }
    int wylosowanyMartwySasiad;
    do {
        wylosowanyMartwySasiad = funkcjeUtility::wylosujInt(0, nSasiednichNiszy - 1);
    } while (nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]] == nullptr || nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]]->bCzyZyje() == true);
    delete nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]];
    nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]] = nullptr;
    return true;
}

char Grzyb::znak() const
{
    return '#';
}
