#include "organizm.h"
#ifndef GLON_H
#define GLON_H


class Glon : public Organizm
{
protected:
    /// Zawsze zwraca prawdę (prowadzi fotosyntezę).
    virtual bool probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;

    virtual Organizm * wygenerujDziecko() override;

    /// Zwraca *
    virtual char znak() const override;
public:
    Glon(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
    virtual ~Glon();
};

#endif // GLON_H
