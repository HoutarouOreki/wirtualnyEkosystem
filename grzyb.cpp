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

void Grzyb::probaPoruszeniaSie()
{
    sprobujPrzemiescicSie();
}

bool Grzyb::probaNajedzeniaSie()
{
    Organizm* sasiad;
    bool istniejeMartwySasiad = false;
    for (unsigned int i = 0; i < getIloscSasiednichNiszy(); i++) {
        if (getNisze()[getPozycjeSasiednichNiszy()[i]] == nullptr) {
            continue;
        }
        sasiad = getNisze()[getPozycjeSasiednichNiszy()[i]];
        if (!sasiad->czyZywy()) {
            istniejeMartwySasiad = true;
            break;
        }
    }
    if (!istniejeMartwySasiad) {
        return false;
    }
    int wylosowanyMartwySasiad;
    do {
        wylosowanyMartwySasiad = funkcjeUtility::wylosujInt(0, getIloscSasiednichNiszy() - 1);
    } while (getNisze()[getPozycjeSasiednichNiszy()[wylosowanyMartwySasiad]] == nullptr ||
             getNisze()[getPozycjeSasiednichNiszy()[wylosowanyMartwySasiad]]->czyZywy() == true);
    wchlonOrganizm(getPozycjeSasiednichNiszy()[wylosowanyMartwySasiad]);
    return true;
}

char Grzyb::znak() const
{
    return Organizm::ZNAK_GRZYBU;
}
