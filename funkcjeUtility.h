#include <string>

#ifndef FUNKCJEUTILITY_H
#define FUNKCJEUTILITY_H

namespace funkcjeUtility {

    int pobierzInt(std::string nazwa);
    int pobierzIntMinMax(std::string nazwa, int min, int max);
    int wylosujInt(int min, int max);
    std::string nacisnijDowolnyKlawisz();
}

#endif // FUNKCJEUTILITY_H
