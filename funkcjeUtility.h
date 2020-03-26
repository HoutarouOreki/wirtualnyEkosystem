#include <string>

#ifndef FUNKCJEUTILITY_H
#define FUNKCJEUTILITY_H

namespace funkcjeUtility
{
    /// Wyświetla komunikat o podanie wartości, którą zwróci.
    /// Komunikt ma postać "Podaj <nazwa>\n>".
    /// Jeśli użytkownik poda wejście, które nie uda się
    /// zamienić na int, wyświetlony zostanie komunikat
    /// o tym informujący oraz użytkownik zostanie
    /// poproszony o ponowne podanie liczby.
    /// pre: brak
    /// Post: Zwrócona została liczba podana przez użytkownika.
    int pobierzInt(std::string nazwa);

    /// Wyświetla komunikat o podanie wartości, którą zwróci,
    /// wraz z dozwolonym zakresem wartości (włącznie od min do max).
    /// Komunikt ma postać "Podaj <nazwa> (od <min> do <max>)\n>".
    /// Jeśli użytkownik poda wejście, które nie uda się
    /// zamienić na int z damegp przedziału, wyświetlony zostanie
    /// komunikat o tym informujący oraz użytkownik zostanie
    /// poproszony o ponowne podanie liczby.
    int pobierzIntMinMax(std::string nazwa, int min, int max);

    /// Losuje liczbę od min do max włącznie.
    int wylosujInt(int min, int max);

    /// Wyświetla ">" oraz akceptuje od użytkownika
    /// wejście zakończone enterem.
    /// pre: brak
    /// post: Zwrócony zostaje podany przez użytkownika ciąg znaków.
    std::string dostanLinie();

    /// Zmienia wartość zmiennej na odwrotną.
    void przelaczBool(bool *wartosc);

    /// Wyświetla liczbę na przestrzeni <lacznaIloscZnakow> znaków.
    /// Jeśli liczbaPoPrawej, to liczba zostanie umieszczona
    /// po prawej stronie tej przestrzeni, w innym wypadku po lewej.
    /// pre: lacznaIloscZnakow musi być w stanie zmieścić liczbę.
    std::string liczbaBialeZnaki(int liczba, unsigned int lacznaIloscZnakow, bool liczbaPoPrawej);

    /// Drukuje <ile> spacji.
    std::string ilesBialychZnakow(unsigned int ile);
}

#endif // FUNKCJEUTILITY_H
