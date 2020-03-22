#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H


class Grzyb : public Organizm
{
protected:
    virtual Organizm * wygenerujDziecko() override;
public:
    Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin);
    virtual bool probaNajedzeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy) override;
    virtual char znak() const override;
    virtual void probaPoruszeniaSie(Organizm **nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy) override;
};

#endif // GRZYB_H
