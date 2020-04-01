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
    /// \post Zwrócona została liczba podana przez użytkownika.
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
    /// \post Zwrócony zostaje podany przez użytkownika ciąg znaków.
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

    /// \brief Próbuje zapisać tekst do pliku o podanej nazwie.
    /// \details Plik będzie znajdował się w folderze, z którego został uruchomiony program.
    /// Jeśli plik o podanej nazwie istnieje, użytkownik będzie mógł
    /// zdecydować, czy go nadpisać.
    /// \param[in] tekst Tekst do zapisania.
    /// \param[in] nazwaPliku Nazwa pliku, do którego zostanie zapisany tekst.
    /// \returns Wynik zapisu.
    bool sprobujZapisacTekstDoPliku(const std::string tekst, const std::string nazwaPliku);

    /// \brief Sprawdza, czy podana nazwa pliku jest przewidywalna/bezpieczna.
    /// \details Nazwa pliku jest uznawana za bezpieczną,
    /// jeśli posiada jedynie litery i/lub cyfry,
    /// oraz posiada od 1 do 12 znaków.
    /// \returns Czy nazwa pliku jest bezpieczna.
    bool czyBezpiecznaNazwaPliku(const std::string nazwaPliku);
}

#endif // FUNKCJEUTILITY_H
