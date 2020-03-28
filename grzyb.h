#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H

/// \brief Organizm oczyszczający \ref Srodowisko "środowisko" z martwych organizmów.
class Grzyb : public Organizm
{
protected:
    /// \copybrief Organizm::wygenerujDziecko()
    /// \returns Grzyb(Organizm::maxWiek,
    /// Organizm::maxNajedzenie, Organizm::kosztNarodzin).
    virtual Organizm *wygenerujDziecko() override;

    /// \brief Szuka w sąsiedztwie martwych \ref Organizm "organizmów".
    /// Jeśli znajdzie, losowo wchłania jednego.
    /// \returns \c true, jeśli udało się znaleźć i zjeść martwy \ref Organizm "organizmów".
    /// \see Organizm::czyZywy()
    virtual bool probaNajedzeniaSie() override;

    /// \copybrief Organizm::znak()
    /// \returns \#
    virtual char znak() const override;

    /// \brief Wywołuje sprobujPrzemiescicSie().
    void probaPoruszeniaSie() override;
public:
    /// \brief Wywołuje konstruktor Organizm::Organizm(\p maxWiek,
    /// \p maxNajedzenie, \p kosztNarodzin, \p poczatkowyWiek).
    /// \param[in] maxWiek
    /// \param[in] maxNajedzenie
    /// \param[in] kosztNarodzin
    /// \param[in] poczatkowyWiek
    Grzyb(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // GRZYB_H
