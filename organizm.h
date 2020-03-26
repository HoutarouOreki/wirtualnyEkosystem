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
    bool bZostalWchloniety;

    /// Szuka wolnych niszy w sąsiedztwie.
    /// Jeśli znajdzie, w jednej z nich
    /// umieszcza swojego potomka.
    /// post: nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] = wygenerujDziecko()
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

    /// Usuwa organizm z tablicy nisze. Jeśli jest żywy,
    /// to ustawia Organizm::bZostalWchloniety tego organizmu
    /// na true, aby Srodowisko wiedziało, aby usunąć
    /// go ze swojej tablicy żywych organizmów.
    /// post: nisze[NrNiszy] = nullptr
    void wchlonOrganizm(unsigned int nrNiszy);

    /// Wywołuje funkcję wchlonOrganizm, a następnie zmienia pozycję
    /// na pozycję tego organizmu.
    /// post: nisze[wlasnyIndeks] = nullptr,
    /// nisze[nrNiszy] = this
    void wchlonOrazZajmijPozycjeOrganizmu(unsigned int nrNiszy);

    /// Szuka wolnej niszy w sąsiedztwie. Jeśli znajdzie,
    /// zmienia swoją pozycję na tę niszę.
    /// post: nisze[wlasnyIndeks] zostaje ustawiona na nullptr,
    /// nisze[pozycjeSasiednichNiszy[wylosowanaNisza]] zostaje ustawiona na this,
    /// wlasnyIndeks zostaje ustawiony na pozycjeSasiednichNiszy[wylosowanaNisza].
    void sprobujPrzemiescicSie();
public:
    Organizm(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
    virtual ~Organizm();

    unsigned int getWiek() const;

    unsigned int getNajedzenie() const;

    unsigned int wlasnyIndeks;

    bool bCzyPrzejedzony() const;
    bool bCzyNajedzony() const;
    bool bCzyZyje() const;
    bool getZostalWchloniety() const;

    /// Jeśli organizm jest żywy, zwraca wartość funkcji znak().
    /// W przeciwnym wypadku zwraca +
    char dostanZnak() const;
    unsigned int getMaxWiek() const;
    unsigned int getMaxNajedzenie() const;

    bool getWlasnieNajadl() const;
    bool getWlasnieRozmnozyl() const;

    /// Dostaje informacje o środowisku i sąsiedztwie (otoczeniu 3x3).
    /// **nisze to wskaźnik do tablicy środowiska z wszystkimi niszami.
    /// *pozycjeSasiednichNiszy to <nSasiednichNiszy> indeksów do tablicy **nisze,
    /// dających dostęp do niszy z sąsiedztwa.
    /// post: Argumenty funkcji zostały zapisane w zmiennych o takich samych nazwach.
    void zobaczSrodowisko(Organizm** nisze, unsigned int* pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy);

    /// Organizm sprawdza, czy to odpowiedni moment na próbę rozmnożenia się,
    /// (jest najedzony).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaRozmnozeniaSie.
    /// post: Zmienna bWlasnieRozmnozyl została ustawiona
    /// ustawiona na wynik probaRozmnozeniaSie.
    void mozeSprobujRozmnozycSie();

    /// Organizm sprawdza, czy to odpowiedni moment na próbę najedzenia się,
    /// (w tym kroku się nie rozmnożył i nie jest przejedzony).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaNajedzeniaSie.
    /// post: jeśli probaNajedzeniaSie zwróciła prawdę, zmienna najedzenie
    /// została powiększona o 1. Zmienna bWlasnieNajadl została
    /// ustawiona na wynik probaNajedzeniaSie.
    void mozeSprobujNajescSie();

    /// Organizm sprawdza, czy to odpowiedni moment na próbę zmianę pozycji,
    /// (w tym kroku się nie najadł i nie rozmnożył).
    /// Jeśli tak, próbuje to zrobić wywołując funkcję probaPoruszeniaSie.
    void mozeSprobujPoruszycSie();

    /// Zmienna wiek zostaje zwiększona o 1.
    void starzenieSie();

    // znaki organizmow
    const static char ZNAK_GLONU = '*';
    const static char ZNAK_GRZYBU = '#';
    const static char ZNAK_BAKTERII = '@';
    const static char ZNAK_MARTWEGO = '+';
};

#endif // ORGANIZM_H
