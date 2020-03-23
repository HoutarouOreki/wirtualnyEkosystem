#include "grzyb.h"
#include "funkcjeUtility.h"

Grzyb::Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin) : Organizm(maxWiek, maxNajedzenie, kosztNarodzin)
{

}

Organizm* Grzyb::wygenerujDziecko()
{
    return new Grzyb(maxWiek, maxNajedzenie, kosztNarodzin);
}

void Grzyb::probaPoruszeniaSie(Organizm**, unsigned int*, unsigned int)
{
    sprobujPrzemiescicSie();
}

bool Grzyb::probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy)
{
    Organizm* sasiad;
    bool istniejeMartwySasiad = false;
    for (unsigned int i = 0; i < nSasiednichNiszy; i++) {
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
    } while (nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]] == nullptr ||
             nisze[pozycjeSasiednichNiszy[wylosowanyMartwySasiad]]->bCzyZyje() == true);
    wchlonOrganizm(pozycjeSasiednichNiszy[wylosowanyMartwySasiad]);
    return true;
}

char Grzyb::znak() const
{
    return Organizm::ZNAK_GRZYBU;
}
