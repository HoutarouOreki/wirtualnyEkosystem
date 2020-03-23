#include <string>

#ifndef FUNKCJEUTILITY_H
#define FUNKCJEUTILITY_H

namespace funkcjeUtility {

    int pobierzInt(std::string nazwa);
    int pobierzIntMinMax(std::string nazwa, int min, int max);
    int wylosujInt(int min, int max);
    std::string dostanLinie();
    void przelaczBool(bool *wartosc);
    void dostanPozycjeKursora(int* kolumna, int* linia);
    void ustawKursor(int kolumna, int linia);
}

#endif // FUNKCJEUTILITY_H
