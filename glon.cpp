#include "glon.h"

Glon::Glon(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin) : Organizm(maxWiek, maxNajedzenie, kosztNarodzin)
{
}

Glon::~Glon()
{
}

bool Glon::probaNajedzeniaSie(Organizm**, unsigned int*, unsigned int)
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
}
