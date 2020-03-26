#ifndef FUNKCJEKONSOLI_H
#define FUNKCJEKONSOLI_H

namespace funkcjeKonsoli
{
    /// Ustawia kursor iloscLinii linijek wyżej.
    /// pre: brak
    /// post: Kursor znajdzie się iloscLinii linijek wyżej na początku linii.
    void cofnijKursor(unsigned int iloscLinii);

    /// Jeśli dany wymiar konsoli jest mniejszy niż podany,
    /// to zostaje powiększony do podanej wartości.\n
    /// pre: brak
    /// post: Konsola ma wielkość o co najmniej podanych wymiarach.
    void powiekszOkno(unsigned int minSzerokosc, unsigned int minWysokosc);
};

#endif // FUNKCJEKONSOLI_H
