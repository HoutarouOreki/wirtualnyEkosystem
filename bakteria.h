#include "organizm.h"

#ifndef BAKTERIA_H
#define BAKTERIA_H


class Bakteria : public Organizm
{
protected:
    bool probaNajedzeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
    void probaPoruszeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
    char znak() const override;
    Organizm * wygenerujDziecko() override;
public:
    Bakteria(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin);
};

#endif // BAKTERIA_H
