#ifndef ORGANIZM_H
#define ORGANIZM_H

/// \brief Klasa Organizm, która jest dziedziczona przez podklasy gatunków.
/// \details Posiada odpowiednie implementacje czynności niezmiennych
/// pomiędzy gatunkami oraz abstrakcyjne funkcje,
/// które powinny być nadpisane przez podklasy gatunków
/// dla czynności różniących się pomiędzy gatunkami.
class Organizm
{
private:
    /// \brief Poziom najedzenia organizmu.
    /// \see czyPrzejedzony(), czyNajedzony()
    unsigned int najedzenie;

    /// \brief Ilość kroków symulacji przeżytych przez organizm.
    /// \see maxWiek, czyZywy(), Srodowisko::wykonajKrokSymulacji(), Srodowisko::krokSymulacji
    unsigned int wiek;

    /// \brief Zapisany wynik ostatniej próby rozmnożenia się.
    bool czyWlasnieRozmnozyl;

    /// \brief Zapisany wynik ostatniej próby najedzenia się.
    bool czyWlasnieNajadl;

    /// \brief Wskaźnik do tablicy organizmów środowiska.
    /// \see Srodowisko::nisze
    Organizm** nisze;

    /// \brief Indeksy niszy w sąsiedztwie.
    unsigned int pozycjeSasiednichNiszy[8];

    /// \brief Ilość niszy wokół tego organizmu.
    /// \details Zazwyczaj wynosi 8, jednak w przypadkach,
    /// gdy organizm znajduje się w niszy
    /// przy brzegu środowiska, jest ich mniej.
    /// Np. gdy znajduje się w kącie, sąsiednich niszy jest tylko 3.
    unsigned int iloscSasiednichNiszy;

    /// \brief \c true, jeśli został wchłonięty podczas bycia żywym.
    /// \details Używane przez Srodowisko, aby wiedziało, żeby
    /// usunąć dany organizm ze swojego vectora Srodowisko::zyweOrganizmy.
    /// \see wchlonOrganizm(unsigned int nrNiszy)
    bool czyZostalWchloniety;

    /// \brief Próbuje umieścić potomka w sąsiedztwie.
    /// \details Szuka wolnych niszy w sąsiedztwie.
    /// Jeśli znajdzie, w jednej z nich umieszcza swojego potomka.
    /// \post #nisze[#pozycjeSasiednichNiszy[wylosowanaNisza]] = wygenerujDziecko()
    /// \returns \c true, jeśli próba się powiodła.
    bool probaRozmnozeniaSie();
protected:
    /// \returns #nisze
    Organizm **getNisze() const;

    /// \returns #pozycjeSasiednichNiszy
    unsigned int* getPozycjeSasiednichNiszy();

    /// \returns #iloscSasiednichNiszy
    unsigned int getIloscSasiednichNiszy() const;

    /// \brief Jeśli #wiek przekroczy tę wartość, organizm staje się martwy.
    /// \see czyZywy()
    unsigned int maxWiek;

    /// \brief Maksymalna wartość zmiennej #najedzenie.
    /// \details Jeśli #najedzenie osiągnie tę wartość, organizm
    /// nie będzie mógł podjąć kolejnych prób najedzenia się.
    /// \see czyNajedzony(), czyPrzejedzony()
    unsigned int maxNajedzenie;

    /// \brief Przy rozmnażaniu się #najedzenie jest zmniejszane o tę wartość.
    unsigned int kosztNarodzin;

    /// \brief Zwraca potomka.
    /// \note Funkcja ta powinna być nadpisana przez poszczególne klasy
    /// organizmów, aby zwracała odpowiednich potomków.
    /// \returns Wskaźnik do potomka.
    virtual Organizm* wygenerujDziecko();

    /// \brief Znak organizmu wyświetlany na planszy środowiska.
    /// \note Funkcja ta powinna być nadpisana przez poszczególne organizmy,
    /// aby zwracała ich odpowiednie znaki.
    /// \returns Znak organizmu.
    virtual char znak() const;

    /// \brief Funkcja wywoływana po zdecydowaniu się na próbę najedzenia się.
    /// \note Powinna być zaimplementowana w dziedziczących klasach organizmów,
    /// i powinna zwracać \c true, jeśli próba się powiodła,
    /// oraz \c false, jeśli się nie powiodła.
    /// \returns \c true, jeśli próba się powiodła.
    virtual bool probaNajedzeniaSie();

    /// \brief Funkcja wywoływana po zdecydowaniu się na próbę najedzenia się.
    /// \note Domyślna implementacja nie wykonuje niczego, więc funkcja ta
    /// powinna być zaimplementowana w dziedziczących klasach organizmów,
    /// które są w stanie się poruszać.
    /// \returns
    virtual void probaPoruszeniaSie();

    /// \brief Pozbywa się innego organizmu ze środowiska.
    /// \details Usuwa organizm z tablicy Srodowisko::nisze na indeksie \p nrNiszy.
    /// Jeśli jest żywy, to ustawia Organizm::czyZostalWchloniety tego
    /// organizmu na \c true, aby Srodowisko wiedziało, aby usunąć
    /// go ze swojego vectora Srodowisko::zyweOrganizmy.
    /// \post #nisze[\p nrNiszy] = \c nullptr
    /// \param[in] nrNiszy to pozycja wchłanianego organizmu
    /// w tablicy #nisze.
    void wchlonOrganizm(const unsigned int nrNiszy);

    /// \brief Pozbywa się innego organizmu ze środowiska i zajmuje jego miejsce.
    /// \details Wywołuje funkcję wchlonOrganizm(unsigned int nrNiszy),
    /// a następnie zmienia pozycję na pozycję tego wchłoniętego organizmu.
    /// \post #nisze[#wlasnyIndeks] = \c nullptr;
    /// #nisze[\c nrNiszy] = \c this
    /// \param[in] nrNiszy to pozycja wchłanianego organizmu
    /// w tablicy #nisze.
    void wchlonOrazZajmijPozycjeOrganizmu(const unsigned int nrNiszy);

    /// \brief Próbuje zmienić swoją pozycję.
    /// \details Szuka wolnej niszy w sąsiedztwie. Jeśli znajdzie,
    /// zmienia swoją pozycję na tę niszę.
    /// \post #nisze[#wlasnyIndeks] zostaje ustawiona na \c nullptr,
    /// #nisze[#pozycjeSasiednichNiszy[\c wylosowanaNisza]] zostaje ustawiona na \c this,
    /// #wlasnyIndeks zostaje ustawiony na #pozycjeSasiednichNiszy[\c wylosowanaNisza].
    void sprobujPrzemiescicSie();
public:
    /// \brief Ustawia zmienne #maxWiek, #maxNajedzenie,
    /// #kosztNarodzin i #wiek na wartości podane w parametrach.
    /// \param[in] maxWiek
    /// \param[in] maxNajedzenie
    /// \param[in] kosztNarodzin
    /// \param[in] poczatkowyWiek
    Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);

    /// \brief Pusty destruktor.
    /// \details Pusty destruktor - klasa nie posiada
    /// pól ani metod wymagających usuwania.
    virtual ~Organizm();

    /// \returns #wiek
    unsigned int getWiek() const;

    /// \returns #najedzenie
    unsigned int getNajedzenie() const;

    /// \brief Indeks tego organizmu w tablicy Srodowisko::nisze.
    unsigned int wlasnyIndeks;

    /// \brief Czy #najedzenie osiągnęło wartość #maxNajedzenie.
    /// \returns \c true, jeśli przejedzony.
    bool czyPrzejedzony() const;

    /// \brief Czy poziom zmiennej #najedzenie przekroczył #kosztNarodzin potomka.
    /// \returns \c true, jeśli najedzony.
    bool czyNajedzony() const;

    /// \brief Czy #wiek nie przekroczył jeszcze wartości #maxWiek.
    /// \returns \c true, jeśli żywy.
    bool czyZywy() const;

    /// \returns #czyZostalWchloniety
    bool getCzyZostalWchloniety() const;

    /// \brief Zwraca znak swojego typu, bądź martwego organizmu.
    /// \details Jeśli organizm jest żywy, zwraca wartość funkcji znak().
    /// W przeciwnym wypadku zwraca Organizm::ZNAK_MARTWEGO.
    /// \see czyZywy()
    /// \returns Znak swojego gatunku bądź znak martwego organizmu.
    char dostanZnak() const;

    /// \returns #maxWiek
    unsigned int getMaxWiek() const;

    /// \returns #maxNajedzenie
    unsigned int getMaxNajedzenie() const;

    /// \returns #czyWlasnieNajadl
    bool getWlasnieNajadl() const;

    /// \returns #czyWlasnieRozmnozyl
    bool getWlasnieRozmnozyl() const;

    /// \brief Dostaje informacje o środowisku i sąsiedztwie (otoczeniu 3x3).
    /// \param[in] nisze to wskaźnik do tablicy środowiska z wszystkimi niszami.
    /// \param[in] pozycjeSasiednichNiszy to \p iloscSasiednichNiszy indeksów do tablicy \p nisze,
    /// dających dostęp do niszy z sąsiedztwa.
    /// \param[in] iloscSasiednichNiszy ile niszy sąsiaduje z tym organizmem.
    /// \post Argumenty funkcji zostały zapisane w zmiennych o takich samych nazwach.
    void zobaczSrodowisko(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int iloscSasiednichNiszy);

    /// \brief Jeśli jest na to odpowiedni moment, organizm próbuje się rozmnożyć.
    /// \details Organizm sprawdza, czy to odpowiedni moment na próbę rozmnożenia się
    /// (czyNajedzony() zwraca \c true).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaRozmnozeniaSie().
    /// \post Zmienna #czyWlasnieRozmnozyl została ustawiona na odpowiednią wartość.
    void mozeSprobujRozmnozycSie();

    /// \brief Jeśli jest na to odpowiedni moment, organizm próbuje się najeść.
    /// \details Organizm sprawdza, czy to odpowiedni moment na próbę najedzenia się
    /// (#czyWlasnieRozmnozyl i czyPrzejedzony() są \c false).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaNajedzeniaSie().
    /// \post Jeśli probaNajedzeniaSie() zwróciła prawdę, zmienna #najedzenie
    /// została powiększona o 1. Zmienna #czyWlasnieNajadl została
    /// ustawiona na wynik probaNajedzeniaSie().
    void mozeSprobujNajescSie();

    /// \brief Jeśli jest na to odpowiedni moment, organizm próbuje się przemieścić.
    /// \details Organizm sprawdza, czy to odpowiedni moment na próbę zmianę pozycji
    /// (#czyWlasnieNajadl i #czyWlasnieRozmnozyl są \c false).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaPoruszeniaSie().
    /// \post Organizm znajduje się na innej pozycji w tablicy Srodowisko::nisze.
    void mozeSprobujPoruszycSie();

    /// \brief Zmienna #wiek zostaje zwiększona o 1.
    void starzenieSie();

    // znaki organizmow
    /// \brief Znak, który reprezentuje gatunek \ref Glon "glonu".
    const static char ZNAK_GLONU = '*';

    /// \brief Znak, który reprezentuje gatunek \ref Grzyb "grzybu".
    const static char ZNAK_GRZYBU = '#';

    /// \brief Znak, który reprezentuje gatunek \ref Bakteria "bakterii".
    const static char ZNAK_BAKTERII = '@';

    /// \brief Znak, który reprezentuje martwe \ref Organizm "organizmy".
    const static char ZNAK_MARTWEGO = '+';
};

#endif // ORGANIZM_H
