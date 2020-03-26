#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H


class Grzyb : public Organizm
{
protected:
    virtual Organizm * wygenerujDziecko() override;

    /// Szuka w sąsiedztwie martwych organizmów.
    /// Jeśli znajdzie, losowo wchłania jednego.
    virtual bool probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;

    /// Zwraca #
    virtual char znak() const override;

    /// Wywołuje sprobujPrzemiescicSie
    virtual void probaPoruszeniaSie(Organizm **nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
public:
    Grzyb(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // GRZYB_H
