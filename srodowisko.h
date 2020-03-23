#include <string>
#include <vector>
#include "organizm.h"
#ifndef SRODOWISKO_H
#define SRODOWISKO_H

class Srodowisko
{
private:
    const unsigned int MAX_SZEROKOSC = 40;
    const unsigned int MAX_WYSOKOSC = 26;
    unsigned int szerokosc;
    unsigned int wysokosc;
    unsigned int krokSymulacji;

    unsigned int iloscGlonow;
    unsigned int iloscGrzybow;
    unsigned int iloscBakterii;
    unsigned int iloscMartwych;
    void podliczIlosciOrganizmow();

    unsigned int dostanIndeks(unsigned int x, unsigned int y) const;
    Organizm* getNisza(unsigned int x, unsigned int y) const;
    void setNisza(Organizm* organizm, unsigned int x, unsigned int y);
    unsigned int dostanX(int indeksNiszy) const;
    unsigned int dostanY(int indeksNiszy) const;
    unsigned int dostanIndeksSasiada(unsigned int x, unsigned int y, unsigned int nrSasiada) const;
    char dostanLitereKolumny(unsigned int nrKolumny) const;

    std::string* informacjeOrganizmow() const;
    std::vector<unsigned int> pozycjeZywychOrganizmow;
    bool upewnijSieCzyOrganizmNadalIstnieje(int i);

    void wyswietlUstawienia();
    std::string dostanKolejnaInformacje(std::string* informacje, unsigned int* indeksInformacji);
public:

    struct ustawieniaWyswietlania
    {
    public:
        enum trybWyswietlania
        {
            krokOrazWyswietlanieSrodowiska,
            wyswietlanieSrodowiska,
            wyswietlanieUstawien,
            zaden
        };

        trybWyswietlania obecnyTryb;

        // czy kolejne kroki symulacji powinny być rysowane na poprzednich (cofanie kursora)
        bool nadrysowywanie;

        bool wyswietlajNajedzenie[3];
        bool wyswietlajRozmnozenie[3];
        bool wyswietlajInfo[3];
    };
    bool czyWyswietlacInfo(char znakOrganizmu) const;
    bool czySygnalizowacNajedzenie(char znakOrganizmu) const;
    bool czySygnalizowacRozmnozenie(char znakOrganizmu) const;
    void wyswietlBoolUstawien(bool zmienna, std::basic_ostream<char>& f(std::basic_ostream<char>&));

    Srodowisko(ustawieniaWyswietlania* ustawieniaWyswietlania);
    ~Srodowisko();

    void wykonajKrokSymulacji();

    Organizm** nisze;

    unsigned int getSzerokosc() const;

    unsigned int getWysokosc() const;

    unsigned int maxWiekGlonow;
    unsigned int maxWiekGrzybow;
    unsigned int maxWiekBakterii;

    unsigned int maxNajedzenieGlonow;
    unsigned int maxNajedzenieGrzybow;
    unsigned int maxNajedzenieBakterii;

    unsigned int kosztNarodzinGlonow;
    unsigned int kosztNarodzinGrzybow;
    unsigned int kosztNarodzinBakterii;

    void wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko);
    void petla();

    ustawieniaWyswietlania* ustWyswietlania;
};

#endif // SRODOWISKO_H
