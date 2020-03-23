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
    unsigned int pozycjeSasiednichNiszy[8];
    unsigned int nSasiednichNiszy;

    // czynności życiowe
    bool probaRozmnozeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy);
protected:
    unsigned int maxWiek;
    unsigned int maxNajedzenie;
    unsigned int kosztNarodzin;
    virtual Organizm* wygenerujDziecko();
    virtual char znak() const;

    // czynności życiowe
    virtual bool probaNajedzeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy);
    virtual void probaPoruszeniaSie(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy);

    void wchlonOrganizm(unsigned int nrNiszy);
    void sprobujPrzemiescicSie();
public:
    Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
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

    void zobaczSrodowisko(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy);

    // czynności życiowe
    void mozeRozmnozSie();
    void mozeSprobujNajescSie();
    void mozeSprobujPoruszycSie();
    void starzenieSie();

    // znaki organizmow
    const static char ZNAK_GLONU = '*';
    const static char ZNAK_GRZYBU = '#';
    const static char ZNAK_BAKTERII = '@';
    const static char ZNAK_MARTWEGO = '+';
};

#endif // ORGANIZM_H
