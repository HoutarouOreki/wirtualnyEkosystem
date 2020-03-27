#include "organizm.h"

#ifndef BAKTERIA_H
#define BAKTERIA_H

/// Organizm agresywny, atakujący \ref Glon "glony" bądź inne bakterie.
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
    /// \brief Szuka w sąsiedztwie organizmów o określonym
    /// znaku i jeśli takie znajdzie, wchłania jeden z nich.
    /// \param[in] znakOrganizmu
    /// \returns wynik próby.
    bool probaNajedzeniaSieOrganizmem(char znakOrganizmu);
protected:
    /// \copybrief Organizm::probaNajedzeniaSie()
    /// \details Najpierw szuka w sąsiedztwie żywych glonów.
    /// Jeśli znajdzie, to wchłanie jednego.
    /// Jeśli nie, szuka w sąsiedztwie innych żywych bakterii.
    /// Jeśli znajdzie, to wchłania jedną.
    /// Jeśli udało się wchłonąć jakiś organizm, przenosi się na jego miejsce.
    /// \returns wynik próby.
    bool probaNajedzeniaSie() override;

    /// Wywołuje funkcję Organizm::sprobujPrzemiescicSie().
    void probaPoruszeniaSie() override;

    /// \copybrief Organizm::znak()
    /// \returns \@
    char znak() const override;

    /// \copybrief Organizm::wygenerujDziecko()
    /// \returns Bakteria(Organizm::maxWiek, Organizm::maxNajedzenie,
    /// Organizm::kosztNarodzin).
    Organizm *wygenerujDziecko() override;
public:
    /// \brief Wywołuje konstruktor Organizm::Organizm(\p maxWiek,
    /// \p maxNajedzenie, \p kosztNarodzin, \p poczatkowyWiek).
    /// \param[in] maxWiek
    /// \param[in] maxNajedzenie
    /// \param[in] kosztNarodzin
    /// \param[in] poczatkowyWiek
    Bakteria(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // BAKTERIA_H
