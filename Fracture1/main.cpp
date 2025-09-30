#include "fraction.h"

#include <iostream>

int main()
{
    Fraction f1{1,2};
    Fraction f2{8,5};

    Fraction f3 = f1 + f2;
    
    std::cout << f3 << std::endl;
    
}


