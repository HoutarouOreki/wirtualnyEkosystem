#ifndef ORGANIZM_H
#define ORGANIZM_H

class Organizm
{
private:
    unsigned int najedzenie;
    unsigned int wiek;
    bool bWlasnieRozmnozyl;
    bool bWlasnieNajadl;
    Organizm** nisze;
    int pozycjeSasiednichNiszy[8];
    int nSasiednichNiszy;

    // czynności życiowe
    bool probaRozmnozeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy);
protected:
    unsigned int maxWiek;
    unsigned int maxNajedzenie;
    unsigned int kosztNarodzin;
    virtual Organizm* wygenerujDziecko();
    virtual char znak() const;

    // czynności życiowe
    virtual bool probaNajedzeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy);
    virtual void probaPoruszeniaSie(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy);
public:
    Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin);
    virtual ~Organizm();

    unsigned int getWiek() const;

    unsigned int getNajedzenie() const;

    unsigned int wlasnyIndeks;

    bool bCzyNajedzony() const;
    bool bCzyZyje() const;

    char dostanZnak() const;
    unsigned int getMaxWiek() const;
    unsigned int getMaxNajedzenie() const;

    bool getWlasnieNajadl() const;
    bool getWlasnieRozmnozyl() const;

    void zobaczSrodowisko(Organizm** nisze, int pozycjeSasiednichNiszy[], int nSasiednichNiszy);

    // czynności życiowe
    void mozeRozmnozSie();
    void mozeSprobujNajescSie();
    void mozeSprobujPoruszycSie();
    void starzenieSie();
};

#endif // ORGANIZM_H
