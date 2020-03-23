#include "funkcjeUtility.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "srodowisko.h"

Srodowisko* srodowisko;

int main()
{
    srand(time(nullptr));
    std::cout << "Wirtualny ekosystem" << std::endl;
    std::string _;
    std::cout << "Wcisnij enter...";
    std::getline(std::cin, _);
    srodowisko = new Srodowisko();
    srodowisko->petla();
    return 0;
}
