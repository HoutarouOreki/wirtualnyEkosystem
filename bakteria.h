#include "organizm.h"

#ifndef BAKTERIA_H
#define BAKTERIA_H

/// Organizm agresywny, atakujący glony.
/// \par Sposób żywienia się:
/// Bakterie najpierw szukają w swoim sąsiedztwie glonów.
/// Jeśli jakieś znajdą - wybierają losowo jednego i go wchłaniają.
/// Jeśli nie - szukają innych bakterii i je pochłaniają.
/// Po wchłonięciu organizmu bakteria zajmuje jego miejsce.
/// Umożliwia to jej żywienie się ciągami glonów
/// bez przypadkowego odwędrowania w przeciwnym kierunku -
/// zwiększa to szanse przetrwania bakterii.
class Bakteria : public Organizm
{
private:
    bool probaNajedzeniaSieOrganizmem(char znakOrganizmu);
protected:
    /// Najpierw szuka w sąsiedztwie żywych glonów.
    /// Jeśli znajdzie, to wchłanie jednego.
    /// Jeśli nie, szuka w sąsiedztwie innych żywych bakterii.
    /// Jeśli znajdzie, to wchłania jedną.
    /// Zajmuje miejsce wchłonionego organizmu.
    bool probaNajedzeniaSie() override;

    /// Wywołuje funkcję Organizm::sprobujPrzemiescicSie
    void probaPoruszeniaSie() override;

    /// Zwraca @
    char znak() const override;

    Organizm * wygenerujDziecko() override;
public:
    Bakteria(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // BAKTERIA_H
