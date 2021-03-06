#include "glon.h"

Glon::Glon(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin, unsigned int poczatkowyWiek)
    : Organizm(maxWiek, maxNajedzenie, kosztNarodzin, poczatkowyWiek)
{
}

bool Glon::probaNajedzeniaSie()
{
    return true;
}

char Glon::znak() const
{
    return Organizm::ZNAK_GLONU;
}

Organizm* Glon::wygenerujDziecko()
{
    return new Glon(maxWiek, maxNajedzenie, kosztNarodzin);
    // odpowiadajacy delete wewnatrz Organizm::wchlonOrganizm
    // oraz Srodowisko::~Srodowisko
}
