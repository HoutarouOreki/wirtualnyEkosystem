#include "organizm.h"

#ifndef GRZYB_H
#define GRZYB_H

/// \brief Organizm oczyszczający Srodowisko z martwych organizmów.
class Grzyb : public Organizm
{
protected:
    /// \brief Zwraca Grzyb(maxWiek, maxNajedzenie, kosztNarodzin).
    virtual Organizm * wygenerujDziecko() override;

    /// \brief Szuka w sąsiedztwie martwych organizmów.
    /// Jeśli znajdzie, losowo wchłania jednego.
    virtual bool probaNajedzeniaSie() override;

    /// \brief Zwraca #
    virtual char znak() const override;

    /// \brief Wywołuje sprobujPrzemiescicSie()
    virtual void probaPoruszeniaSie() override;
public:
    /// \copydoc Organizm(unsigned int const, unsigned int const, unsigned int const, unsigned int const)
    Grzyb(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // GRZYB_H
