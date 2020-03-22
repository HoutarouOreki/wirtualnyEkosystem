#ifndef ORGANIZM_H
#define ORGANIZM_H

class Organizm
{
private:
    unsigned int najedzenie;
    unsigned int wiek;
protected:
    unsigned int maxWiek;
    unsigned int maxNajedzenie;
    unsigned int kosztNarodzin;
    virtual bool bProbaNajedzeniaSie(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow);
    bool bProbaRozmnozeniaSie(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow);
    virtual void koniecKroku(bool czyJadl, bool czyRozmnozylSie, Organizm** nisze, int pozycjeSasiadow[], int nSasiadow);
    virtual Organizm* wygenerujDziecko();
    virtual char znak() const;
public:
    Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin);
    virtual ~Organizm();

    unsigned int getWiek() const;

    unsigned int getNajedzenie() const;

    unsigned int wlasnyIndeks;

    bool bCzyNajedzony() const;
    bool bCzyZyje() const;

    virtual void krokSymulacji(Organizm** nisze, int pozycjeSasiadow[], int nSasiadow);
    char dostanZnak() const;
    unsigned int getMaxWiek() const;
    unsigned int getMaxNajedzenie() const;
};

#endif // ORGANIZM_H
