#include "organizm.h"
#ifndef GLON_H
#define GLON_H

/// Organizm pasywny, prowadzący fotosyntezę.
class Glon : public Organizm
{
protected:
    /// \brief Próba najedzenia się. Jako, że prowadzi
    /// fotosyntezę, zawsze się ona udaje.
    /// \returns \c true
    virtual bool probaNajedzeniaSie() override;

    /// \copybrief
    /// \returns Glon(Organizm::maxWiek, Organizm::maxNajedzenie, Organizm::kosztNarodzin).
    virtual Organizm *wygenerujDziecko() override;

    /// \copybrief Organizm::znak()
    /// \returns *
    virtual char znak() const override;
public:
    /// \brief Wywołuje konstruktor Organizm::Organizm(\p maxWiek,
    /// \p maxNajedzenie, \p kosztNarodzin, \p poczatkowyWiek).
    /// \param[in] maxWiek
    /// \param[in] maxNajedzenie
    /// \param[in] kosztNarodzin
    /// \param[in] poczatkowyWiek
    Glon(unsigned int const maxWiek, unsigned int const maxNajedzenie, unsigned int const kosztNarodzin, unsigned int const poczatkowyWiek = 0);
};

#endif // GLON_H
