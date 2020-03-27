#include <string>
#include <vector>
#include "organizm.h"
#ifndef SRODOWISKO_H
#define SRODOWISKO_H

class Srodowisko
{
private:
    /// Maksymalna ilość niszy w wymiarze horyzontalnym.
    const unsigned int MAX_SZEROKOSC = 40;

    /// Maksymalna ilość niszy w wymiarze wertykalnym.
    const unsigned int MAX_WYSOKOSC = 26;

    /// Ilość niszy w wymiarze horyzontalnym.
    unsigned int szerokosc;

    /// Ilość niszy w wymiarze wertykalnym.
    unsigned int wysokosc;

    /// Ile kroków symulacji zostało wykonanych.
    unsigned int krokSymulacji;

    unsigned int iloscGlonow;
    unsigned int iloscGrzybow;
    unsigned int iloscBakterii;
    unsigned int iloscMartwych;

    /// Ustawia wartości zmiennych \a #iloscGlonow, \a #iloscGrzybow
    /// \a #iloscBakterii, \a #iloscMartwych.
    void podliczIlosciOrganizmow();

    /// Zwraca jaki indeks w tablicy \a nisze ma nisza na podanych koordynatach.
    /// \param x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    unsigned int getIndeksNiszyOdKoordynat(const unsigned int x, const unsigned int y) const;

    /// Zwraca organizm zajmujący niszę na podanych koordynatach w tablicy nisze.
    /// Jeśli żaden organizm jej nie zajmuje, zwraca nullptr.
    /// \param x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    Organizm* getNisza(const unsigned int x, const unsigned int y) const;

    /// Umieszcza organizm na podanych koordynatach w tablicy nisze. Jeśli
    /// żaden organizm jej nie zajmuje, zwraca nullptr.
    /// \param x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    /// \post organizm->wlasnyIndeks zostal odpowiednio zmieniony.
    void setNisza(Organizm* organizm, const unsigned int x, const unsigned int y);

    /// Zwraca liczoną od 0 horyzontalną koordynatę niszy na danym indeksie.
    unsigned int dostanX(const unsigned int indeksNiszy) const;

    /// Zwraca liczoną od 0 wertykalną koordynatę niszy na danym indeksie.
    unsigned int dostanY(const unsigned int indeksNiszy) const;

    /// Zwraca indeks niszy w tablicy nisze sąsiada o podanym numerze.
    /// \param x Horyzontalny, liczony od zera, indeks niszy,
    /// której indeks sąsiada zostanie zwrócony.
    /// \param y Wertykalny, liczony od zera, indeks niszy,
    /// której indeks sąsiada zostanie zwrócony.
    /// \param nrSasiada Liczony od zera nr sąsiada, zaczynając od lewego górnego,
    /// następnie idąc w prawo, a następnie w dół.
    /// 0 = po lewej u góry, 7 = po prawej u dołu.
    /// \return
    unsigned int dostanIndeksSasiada(unsigned int x, unsigned int y, const unsigned int nrSasiada) const;

    /// Zwraca literę danej kolumny, pierwsza kolumna (0) ma literę A, druga (1) B, itd...,
    /// kolumna 26 (25) = Z, kolumna 27 (26) = a.
    /// \param nrKolumny Liczony od zera nr kolumny.
    char dostanLitereKolumny(unsigned int nrKolumny) const;

    /// Zwraca tablicę napisów, gdzie każdy z nich opisuje
    /// pozycję, nazwę, wiek oraz najedzenie
    /// i sygnalizację zmiany najedzenia jednego organizmu.
    std::string* informacjeOrganizmow() const;

    /// Przechowuje wskaźniki do żywych organizmów,
    /// aby nie musieć za każdym razem przechodzić każdego
    /// indeksu tablicy "nisze". Prawdopodobnie nie daje to
    /// żadnego realnego zysku, jednak niczego też nie pogarsza,
    /// więc pozostawiam.
    std::vector<Organizm*> zyweOrganizmy;

    /// Sprawdza, czy organizm znajdujący się na podanym indeksie
    /// nie został wchłonięty. Jeśli nadal żyje, zwraca true.
    /// \param i Indeks organizmu.
    bool upewnijSieCzyOrganizmNadalIstnieje(const unsigned int i);

    /// Wyświetla na wyjściu informacje o obecnych ustawieniach
    /// oraz sposobach ich zmiany.
    void wyswietlUstawienia();

    /// Zwraca kolejnego stringa z podanej tablicy \a informacje.
    /// \param informacje Tablica napisów.
    /// \param indeksInformacji Indeks oznaczający, która informacja
    /// powinna zostać zwrócona. Zostanie powiększony o 1.
    std::string dostanKolejnaInformacje(std::string* informacje, unsigned int* indeksInformacji);
    unsigned int dostanNrOrganizmu(char znakOrganizmu) const;
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

    /// Najpierw udostępnia wszystkim żywym organizmom
    /// informacje o wszystkich niszach oraz o sąsiedztwie.
    /// Następnie, w oddzielnych krokach dla wszystkich organizmów
    /// żywych na początku wywołania funkcji, dopóki są żywe i niewchłonięte,
    /// jednocześnie dla wszystkich z nich:
    /// wywołuje zastanawienie się w organizmach nad rozmnożeniem się,
    /// następnie nad najedzeniem się, starzenie się,
    /// oraz finalnie zastanowienie nad przemieszczeniem się.
    /// \post \ref Srodowisko::krokSymulacji został zwiększony o 1.
    void wykonajKrokSymulacji();

    /// \brief Tablica przechowująca wskaźniki do organizmów na odpowiadających im pozycjach.
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

    /// Wyświetla w pierwszej kolumnie ilość wykonanych kroków,
    /// aktualne ilości organizmów w środowisku,
    /// oraz planszę wyświetlającą nisze środowiska z organizmami,
    /// a w drugiej kolumnie wyświetla pozycje organizmów,
    /// ich nazwy, wiek, oraz najedzenie.
    void wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko);

    /// Udostępnia użytkownikowi interfejs obsługi
    /// środowiska oraz nim zarządza.
    void petla();

    ustawieniaWyswietlania* ustWyswietlania;
};

#endif // SRODOWISKO_H
