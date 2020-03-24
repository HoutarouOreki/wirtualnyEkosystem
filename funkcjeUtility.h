#include <string>

#ifndef FUNKCJEUTILITY_H
#define FUNKCJEUTILITY_H

namespace funkcjeUtility
{
    int pobierzInt(std::string nazwa);
    int pobierzIntMinMax(std::string nazwa, int min, int max);
    int wylosujInt(int min, int max);
    std::string dostanLinie();
    void przelaczBool(bool *wartosc);
    std::string liczbaBialeZnaki(int liczba, unsigned int lacznaIloscZnakow, bool liczbaPoPrawej);
    std::string ilesBialychZnakow(unsigned int ile);
}

#endif // FUNKCJEUTILITY_H
