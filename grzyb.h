#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H


class Grzyb : public Organizm
{
protected:
    virtual Organizm * wygenerujDziecko() override;
    virtual void koniecKroku(bool czyJadl, bool czyRozmnozylSie, Organizm **nisze, int pozycjeSasiadow[], int nSasiadow) override;
public:
    Grzyb(unsigned int maxWiek, unsigned int maxNajedzenie, unsigned int kosztNarodzin);
    virtual bool bProbaNajedzeniaSie(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow) override;
    virtual char znak() const override;
};

#endif // GRZYB_H
