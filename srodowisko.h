#include <string>
#include <vector>
#include "organizm.h"
#ifndef SRODOWISKO_H
#define SRODOWISKO_H

/// \brief Wewnątrz środowiska rozwijają się różne gatunki \ref Organizm "organizmów".
/// \details Ich czynności życiowe (żywienie, rozmnażanie oraz poruszanie się)
/// są wykonywane podczas \ref wykonajKrokSymulacji() "kroków symulacji".
class Srodowisko
{
private:
    /// \brief Maksymalna ilość niszy w wymiarze horyzontalnym.
    const unsigned int MAX_SZEROKOSC = 40;

    /// \brief Maksymalna ilość niszy w wymiarze wertykalnym.
    const unsigned int MAX_WYSOKOSC = 26;

    /// \brief Ilość niszy w wymiarze horyzontalnym.
    unsigned int szerokosc;

    /// \brief Ilość niszy w wymiarze wertykalnym.
    unsigned int wysokosc;

    /// \brief Ile kroków symulacji zostało wykonanych.
    unsigned int krokSymulacji;

    /// \brief Ile \ref Glon "glonów" aktualnie żyje w tym środowisku.
    /// \see Organizm::czyZywy()
    unsigned int iloscGlonow;

    /// \brief Ile \ref Grzyb "grzybów" aktualnie żyje w tym środowisku.
    /// \see Organizm::czyZywy()
    unsigned int iloscGrzybow;

    /// \brief Ile \ref Bakteria "bakterii" aktualnie żyje w tym środowisku.
    /// \see Organizm::czyZywy()
    unsigned int iloscBakterii;

    /// \brief Ile martwych \ref Organizm "organizmów" aktualnie znajduje się w środowisku.
    /// \see Organizm::czyZywy()
    unsigned int iloscMartwych;

    /// \brief Ustawia wartości zmiennych #iloscGlonow, #iloscGrzybow
    /// #iloscBakterii, #iloscMartwych.
    void podliczIlosciOrganizmow();

    /// \brief Zwraca jaki indeks w tablicy #nisze ma nisza na podanych koordynatach.
    /// \param[in] x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param[in] y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    /// \returns indeks niszy.
    unsigned int indeksNiszyOdKoordynat(const unsigned int x, const unsigned int y) const;

    /// \brief Zwraca \ref Organizm "organizm" zajmujący niszę na podanych
    /// koordynatach w tablicy #nisze.
    /// \details Jeśli nie ma tam żadnego organizmu, zwraca nullptr.
    /// \param[in] x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param[in] y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    /// \returns Wskaźnik do organizmu lub nullptr.
    Organizm* getNisza(const unsigned int x, const unsigned int y) const;

    /// \brief Umieszcza \ref Organizm "organizm" na podanych koordynatach w tablicy #nisze.
    /// \details Jeśli żaden organizm jej nie zajmuje, zwraca nullptr.
    /// \param[in, out] organizm Wskaźnik do organizmu.
    /// \param[in] x Horyzontalna koordynata niszy, dla pierwszej kolumny wynosi zero.
    /// \param[in] y Wertykalna koordynata niszy, dla pierwszego wiersza wynosi zero.
    /// \post organizm->wlasnyIndeks zostal odpowiednio zmieniony.
    void setNisza(Organizm* const organizm, const unsigned int x, const unsigned int y);

    /// \brief Zwraca liczoną od 0 horyzontalną koordynatę niszy na danym indeksie.
    /// \returns horyzontalną koordynatę niszy.
    /// \param[in] indeksNiszy w tablicy #nisze.
    unsigned int dostanX(const unsigned int indeksNiszy) const;

    /// \brief Zwraca liczoną od 0 wertykalną koordynatę niszy na danym indeksie.
    /// \returns wertykalną koordynatę niszy.
    /// \param[in] indeksNiszy w tablicy #nisze.
    unsigned int dostanY(const unsigned int indeksNiszy) const;

    /// \brief Zwraca indeks niszy w tablicy #nisze sąsiada o podanym numerze.
    /// \param x Horyzontalny, liczony od zera, indeks niszy,
    /// której indeks sąsiada zostanie zwrócony.
    /// \param y Wertykalny, liczony od zera, indeks niszy,
    /// której indeks sąsiada zostanie zwrócony.
    /// \param nrSasiada Liczony od zera nr sąsiada, zaczynając od lewego górnego,
    /// następnie idąc w prawo, a następnie w dół.
    /// 0 = po lewej u góry, 7 = po prawej u dołu.
    /// \returns indeks sąsiada
    unsigned int dostanIndeksSasiada(unsigned int x, unsigned int y, const unsigned int nrSasiada) const;

    /// \brief Zwraca literę danej kolumny.
    /// \details Pierwsza kolumna (0) ma literę A, druga (1) B, itd...,
    /// kolumna 26 (25) = Z, kolumna 27 (26) = a.
    /// \param nrKolumny Liczony od zera indeks kolumny.
    /// \returns Literę kolumny.
    char dostanLitereKolumny(unsigned int nrKolumny) const;

    /// \brief Tablica napisów z informacjami o organizmach.
    /// \details Generuje i zwraca wskaźnik do nowej tablicy napisów,
    /// gdzie każdy z nich opisuje pozycję, nazwę, wiek oraz najedzenie
    /// i sygnalizację zmiany najedzenia jednego organizmu.
    /// Napisy dla danego gatunku nie są generowane,
    /// jeśli czyWyswietlacInfo(\p znakGatunku) zwraca \c false.
    /// \returns Wskaźnik do nowej tablicy napisów.
    std::string* informacjeOrganizmow() const;

    /// \brief Wskaźniki do żywych organizmów.
    /// \details Przechowuje wskaźniki do żywych organizmów,
    /// aby nie musieć za każdym razem przechodzić każdego
    /// indeksu tablicy "nisze".
    /// \note Prawdopodobnie nie daje to
    /// żadnego realnego zysku, jednak niczego też nie pogarsza,
    /// więc pozostawiam.
    std::vector<Organizm*> zyweOrganizmy;

    /// \brief Sprawdza, czy \ref Organizm "organizm" nadal żyje.
    /// \details Czy organizm znajdujący się na podanym indeksie
    /// w tablicy #zyweOrganizmy nie został wchłonięty.
    /// \param i Indeks organizmu.
    /// \returns \c true, jeśli organizm nadal żyje.
    /// \see Organizm::czyZywy()
    bool upewnijSieCzyOrganizmNadalIstnieje(const unsigned int i);

    /// \brief Wyświetla na wyjściu informacje o obecnych ustawieniach
    /// oraz sposobach ich zmiany.
    void wyswietlUstawienia();

    /// \brief Zwraca kolejnego stringa z podanej tablicy \p *informacje.
    /// \param[in] informacje Tablica napisów.
    /// \param[in, out] *indeksInformacji Indeks oznaczający, która informacja
    /// powinna zostać zwrócona. Zostanie powiększony o 1.
    /// \returns Napis z tablicy.
    std::string dostanKolejnaInformacje(std::string* informacje, unsigned int* indeksInformacji);

    /// \brief Zwraca indeks danego typu organizmu w tablicach
    /// w \ref ustawieniaWyswietlania "ustawieniach wyświetlania".
    /// \param[in] znakOrganizmu
    /// \return
    /// \li 0 dla Organizm::ZNAK_GLONU
    /// \li 1 dla Organizm::ZNAK_GRZYBU
    /// \li 2 dla Organizm::ZNAK_BAKTERII
    /// \li 3 dla innych znaków
    unsigned int dostanNrOrganizmu(const char znakOrganizmu) const;
public:

    /// \brief Struktura przechowująca opcje dla funkcji
    /// Srodowisko::wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko).
    struct ustawieniaWyswietlania
    {
    public:
        /// \brief Enumerator zawierający opcje oznaczające co powinno być aktualnie wyświetlane.
        enum trybWyswietlania
        {
            krokOrazWyswietlanieSrodowiska,
            wyswietlanieSrodowiska,
            wyswietlanieUstawien,
            zaden
        };

        /// \brief Co powinno być aktualnie wyświetlane.
        trybWyswietlania obecnyTryb;

        /// \brief Czy kolejne kroki symulacji powinny być rysowane w miejscu poprzednich.
        /// \details Jesli \c true, przy szybkim wykonywaniu kroków konsola nie będzie "migać",
        /// jednak nie będzie też widać poprzednich kroków symulacji.
        bool nadrysowywanie;

        /// \brief Czy dany typ organizmu powinien być podświetlany na żółto przy najedzeniu się.
        /// \details Indeksy typów organizmów:\n
        /// 0 --- \ref Glon "glony"\n
        /// 1 --- \ref Grzyb "grzyby"\n
        /// 2 --- \ref Bakteria "bakterie"
        bool wyswietlajNajedzenie[3];

        /// \brief Czy dany typ organizmu powinien być podświetlany na różowo po rozmnożeniu się.
        /// \copydetails wyswietlajNajedzenie
        bool wyswietlajRozmnozenie[3];

        /// \brief Czy po prawej stronie planszy powinny być wyświetlane informacje o danym typie organizmu.
        /// \copydetails wyswietlajNajedzenie
        bool wyswietlajInfo[3];
    };

    /// \brief Struktura gromadząca statystyki dotyczące środowiska.
    /// \details Zapisuje ilość żyjących organizmów danego gatunku
    /// żyjących po danym kroku symulacji, ile z nich się najadło
    /// oraz ile z nich się rozmnożyło. Indeksy vectorów odpowiadają
    /// stanowi po kroku symulacji o numerze indeksu.
    struct statystykiSrodowiska
    {
    public:
        /// \returns const reference do #ilosciGlonow
        const std::vector<unsigned int> &getIlosciGlonow() const;

        /// \returns const reference do #ilosciGrzybow
        const std::vector<unsigned int> &getIlosciGrzybow() const;

        /// \returns const reference do #ilosciBakterii
        const std::vector<unsigned int> &getIlosciBakterii() const;

        /// \returns const reference do #ilosciMartwych
        const std::vector<unsigned int> &getIlosciMartwych() const;

        /// \returns const reference do #ilosciNajedzonychGrzybow
        const std::vector<unsigned int> &getIlosciNajedzonychGrzybow() const;

        /// \returns const reference do #ilosciNajedzonychBakterii
        const std::vector<unsigned int> &getIlosciNajedzonychBakterii() const;

        /// \returns const reference do #ilosciRozmnozonychGlonow
        const std::vector<unsigned int> &getIlosciRozmnozonychGlonow() const;

        /// \returns const reference do #ilosciRozmnozonychGrzybow
        const std::vector<unsigned int> &getIlosciRozmnozonychGrzybów() const;

        /// \returns const reference do #ilosciRozmnozonychBakterii
        const std::vector<unsigned int> &getIlosciRozmnozonychBakterii() const;

        /// \brief Dopisuje statystyki dotyczące stanu
        /// środowiska po ostatnim kroku symulacji.
        /// \param[in] srodowisko którego statystyki zostaną dopisane.
        void dodajStatystykiOstatniegoKroku(Srodowisko* const srodowisko);

    private:
        /// \brief Vector gromadzący ilości żywych \ref Glon "glonów" po danym kroku symulacji.
        std::vector<unsigned int> ilosciGlonow;

        /// \brief Vector gromadzący ilości żywych \ref Grzyb "grzybów" po danym kroku symulacji.
        std::vector<unsigned int> ilosciGrzybow;

        /// \brief Vector gromadzący ilości żywych \ref Bakteria "bakterii" po danym kroku symulacji.
        std::vector<unsigned int> ilosciBakterii;

        /// \brief Vector zapisujący ilości martwych \ref Organizm "organizmów".
        std::vector<unsigned int> ilosciMartwych;

        /// \brief Vector zapisujący ile \ref Grzyb "grzybów"
        /// pożywiło się w danym kroku symulacji.
        std::vector<unsigned int> ilosciNajedzonychGrzybow;

        /// \brief Vector zapisujący ile \ref Bakteria "bakterii"
        /// pożywiło się w danym kroku symulacji.
        std::vector<unsigned int> ilosciNajedzonychBakterii;

        /// \brief Vector zapisujący ile \ref Glon "glonów"
        /// rozmnożyło się w danym kroku symulacji.
        std::vector<unsigned int> ilosciRozmnozonychGlonow;

        /// \brief Vector zapisujący ile \ref Grzyb "grzybów"
        /// rozmnożyło się w danym kroku symulacji.
        std::vector<unsigned int> ilosciRozmnozonychGrzybow;

        /// \brief Vector zapisujący ile \ref Bakteria "bakterii"
        /// rozmnożyło się w danym kroku symulacji.
        std::vector<unsigned int> ilosciRozmnozonychBakterii;
    };

    /// \brief Zwraca wartość z tablicy
    /// #ustWyswietlania->\ref ustawieniaWyswietlania::wyswietlajInfo
    /// "wyswietlajInfo" z indeksu odpowiadającego
    /// \ref Organizm "organizmowi" o danym znaku.
    /// \param[in] znakOrganizmu Znak \ref Organizm "organizmu".
    /// \returns wartość z tablicy #ustWyswietlania->wyswietlajInfo
    bool czyWyswietlacInfo(const char znakOrganizmu) const;

    /// \brief Zwraca wartość z tablicy
    /// #ustWyswietlania->\ref ustawieniaWyswietlania::wyswietlajNajedzenie
    /// "wyswietlajNajedzenie" z indeksu odpowiadającego
    /// \ref Organizm "organizmowi" o danym znaku.
    /// \param[in] znakOrganizmu Znak \ref Organizm "organizmu".
    /// \returns wartość z tablicy #ustWyswietlania->wyswietlajNajedzenie
    bool czySygnalizowacNajedzenie(const char znakOrganizmu) const;

    /// \brief Zwraca wartość z tablicy
    /// #ustWyswietlania->\ref ustawieniaWyswietlania::wyswietlajRozmnozenie
    /// "wyswietlajRozmnozenie" z indeksu odpowiadającego
    /// \ref Organizm "organizmowi" o danym znaku.
    /// \param[in] znakOrganizmu Znak \ref Organizm "organizmu".
    /// \returns wartość z tablicy #ustWyswietlania->wyswietlajRozmnozenie
    bool czySygnalizowacRozmnozenie(const char znakOrganizmu) const;

    /// \brief Wyświetla pokolorowaną wartość zmiennej \c bool i ustawia kolor tekstu.
    /// \param[in] zmienna
    /// \param[in] f operator TermColoru oznaczający kolor tekstu,
    /// jaki powinien być ustawiony po wyświetleniu wartości zmiennej.
    void wyswietlBoolUstawien(const bool zmienna, std::basic_ostream<char>& f(std::basic_ostream<char>&));

    /// \brief Pyta użytkownika o konfigurację parametrów środowiska
    /// i losuje właściwości \ref Organizm "organizmów".
    /// \details Prosi użytkownika o podanie \ref szerokosc "szerokości" i
    /// \ref wysokosc "wysokości", początkowych liczebności organizmów,
    /// oraz losuje własności Organizm::maxWiek, Organizm::maxNajedzenie,
    /// Organizm::kosztNarodzin dla każdego gatunku \ref Organizm "organizmów".
    /// \param[in] ustawieniaWyswietlania wskaźnik, który zostaje
    /// przechowany w #ustWyswietlania.
    Srodowisko(ustawieniaWyswietlania* ustawieniaWyswietlania);

    /// \brief Wywołuje destruktory wszystkich \ref Organizm "organizmów"
    /// oraz zwalnia miejsce zajmowane przez tablicę #nisze.
    ~Srodowisko();

    /// \brief Wywołuje czynności życiowe w \ref Organizm "organizmach".
    /// \details Najpierw udostępnia wszystkim żywym organizmom
    /// informacje o wszystkich niszach oraz o sąsiedztwie.
    /// Następnie, w oddzielnych krokach dla wszystkich organizmów
    /// żywych na początku wywołania funkcji, dopóki są żywe i niewchłonięte,
    /// jednocześnie dla wszystkich z nich:
    /// wywołuje zastanawienie się w organizmach nad rozmnożeniem się,
    /// następnie nad najedzeniem się, starzenie się,
    /// oraz finalnie zastanowienie nad przemieszczeniem się.
    /// Wywołuje statystykiSrodowiska::dodajStatystykiOstatniegoKroku(srodowisko).
    /// \post \ref Srodowisko::krokSymulacji został zwiększony o 1.
    void wykonajKrokSymulacji();

    /// \brief Tablica przechowująca wskaźniki do organizmów na odpowiadających im pozycjach.
    Organizm** nisze;

    /// \returns #szerokosc
    unsigned int getSzerokosc() const;

    /// \returns #wysokosc
    unsigned int getWysokosc() const;

    /// \brief Wyświetla planszę środowiska oraz informacje o organizmach.
    /// \details Wyświetla w pierwszej kolumnie ilość wykonanych kroków,
    /// aktualne ilości organizmów w środowisku,
    /// oraz planszę wyświetlającą nisze środowiska z organizmami,
    /// a w drugiej kolumnie wyświetla pozycje organizmów,
    /// ich nazwy, wiek, oraz najedzenie.
    /// \param[in] czyOstatnioDrukowanoSrodowisko to zmienna informująca o tym,
    /// czy ostatnio wyświetlono planszę środowiska, co jest jednoznaczne z tym,
    /// że można ją nadrysować.
    void wyswietlSrodowisko(bool czyOstatnioDrukowanoSrodowisko);

    /// \brief Udostępnia użytkownikowi interfejs obsługi środowiska.
    void petla();

    /// \brief Opcje wyświetlania używane w wyswietlSrodowisko(bool).
    ustawieniaWyswietlania* ustWyswietlania;

    /// \brief Statystyki tego środowiska.
    statystykiSrodowiska statystyki;
};

#endif // SRODOWISKO_H
