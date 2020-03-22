#include "organizm.h"
#ifndef GLON_H
#define GLON_H


class Glon : public Organizm
{
protected:
    virtual bool probaNajedzeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy) override;
    virtual Organizm * wygenerujDziecko() override;
public:
    Glon(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin);
    virtual ~Glon();
    virtual char znak() const override;
};

#endif // GLON_H
