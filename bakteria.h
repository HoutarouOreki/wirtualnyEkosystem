#include "organizm.h"

#ifndef BAKTERIA_H
#define BAKTERIA_H

/// Organizm jedzący żywe glony bądź żywe bakterie.
class Bakteria : public Organizm
{
private:
    bool probaNajedzeniaSieOrganizmem(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy, char znakOrganizmu);
protected:
    /// Najpierw szuka w sąsiedztwie żywych glonów.
    /// Jeśli znajdzie, to wchłanie jednego.
    /// Jeśli nie, szuka w sąsiedztwie innych żywych bakterii.
    /// Jeśli znajdzie, to wchłania jedną.
    /// Zajmuje miejsce wchłonionego organizmu.
    bool probaNajedzeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;

    /// Wywołuje funkcję Organizm::sprobujPrzemiescicSie
    void probaPoruszeniaSie(Organizm **nisze, unsigned int *pozycjeSasiednichNiszy, unsigned int nSasiednichNiszy) override;

    /// Zwraca @
    char znak() const override;

    Organizm * wygenerujDziecko() override;
public:
    Bakteria(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // BAKTERIA_H
