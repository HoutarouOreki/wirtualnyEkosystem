#include "organizm.h"
#ifndef GLON_H
#define GLON_H


class Glon : public Organizm
{
protected:
    virtual bool probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
    virtual Organizm * wygenerujDziecko() override;
    virtual char znak() const override;
public:
    Glon(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin);
    virtual ~Glon();
};

#endif // GLON_H
