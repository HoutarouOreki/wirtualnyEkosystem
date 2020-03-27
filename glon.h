#include "organizm.h"
#ifndef GLON_H
#define GLON_H

/// Organizm pasywny, prowadzący fotosyntezę.
/// \par Sposób żywienia się:
/// Prowadzi fotosyntezę - w każdym kroku symulacji,
/// w którym próbuje się najeść, udaje mu się to.
class Glon : public Organizm
{
protected:
    /// Zawsze zwraca prawdę (prowadzi fotosyntezę).
    virtual bool probaNajedzeniaSie() override;

    /// Zwraca Glon(maxWiek, maxNajedzenie, kosztNarodzin).
    virtual Organizm * wygenerujDziecko() override;

    /// Zwraca *
    virtual char znak() const override;
public:
    Glon(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // GLON_H
