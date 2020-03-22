#include "grzyb.h"
#include "funkcjeUtility.h"

Grzyb::Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin) : Organizm(maxWiek, maxNajedzenie, kosztNarodzin)
{

}

Organizm* Grzyb::wygenerujDziecko()
{
    return new Grzyb(maxWiek, maxNajedzenie, kosztNarodzin);
}

void Grzyb::koniecKroku(bool czyJadl, bool czyRozmnozylSie, Organizm **nisze, int pozycjeSasiadow[], int nSasiadow)
{
    bool czyMoznaSiePrzemiescic = false;
    for (int i = 0; i < nSasiadow; i++) {
        if (nisze[pozycjeSasiadow[i]] == nullptr) {
            czyMoznaSiePrzemiescic = true;
            break;
        }
    }
    if (!czyMoznaSiePrzemiescic) {
        return;
    }
    if (!czyJadl && !czyRozmnozylSie) {
        int wylosowanaNisza;
        nisze[wlasnyIndeks] = nullptr;
        do {
            wylosowanaNisza = funkcjeUtility::wylosujInt(0, nSasiadow - 1);
        } while (nisze[pozycjeSasiadow[wylosowanaNisza]] != nullptr);
        nisze[pozycjeSasiadow[wylosowanaNisza]] = this;
    }
}

bool Grzyb::bProbaNajedzeniaSie(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow)
{
    Organizm* sasiad;
    bool istniejeMartwySasiad = false;
    for (int i = 0; i < nSasiadow; i++) {
        if (nisze[pozycjeSasiadow[i]] == nullptr) {
            continue;
        }
        sasiad = nisze[pozycjeSasiadow[i]];
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
        wylosowanyMartwySasiad = funkcjeUtility::wylosujInt(0, nSasiadow - 1);
    } while (nisze[pozycjeSasiadow[wylosowanyMartwySasiad]] == nullptr || nisze[pozycjeSasiadow[wylosowanyMartwySasiad]]->bCzyZyje() == true);
    delete nisze[pozycjeSasiadow[wylosowanyMartwySasiad]];
    nisze[pozycjeSasiadow[wylosowanyMartwySasiad]] = nullptr;
    return true;
}

char Grzyb::znak() const
{
    return '#';
}
