#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H


class Grzyb : public Organizm
{
protected:
    virtual Organizm * wygenerujDziecko() override;
    virtual bool probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
    virtual char znak() const override;
    virtual void probaPoruszeniaSie(Organizm **nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;
public:
    Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin);
};

#endif // GRZYB_H
