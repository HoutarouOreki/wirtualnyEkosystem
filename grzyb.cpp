#include "grzyb.h"
#include "funkcjeUtility.h"

Grzyb::Grzyb(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek)
    : Organizm(maxWiek, maxNajedzenie, kosztNarodzin, poczatkowyWiek)
{

}

Organizm* Grzyb::wygenerujDziecko()
{
    return new Grzyb(maxWiek, maxNajedzenie, kosztNarodzin);
    // odpowiadajacy delete wewnatrz Organizm::wchlonOrganizm
    // oraz Srodowisko::~Srodowisko
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
