#include "fraction.h"
#include <iostream>

int main() {
    Fraction a(1, 2);
    Fraction b(3, 4);

    std::cout << "a = " << a.str() << "\n";
    std::cout << "b = " << b.str() << "\n";

    std::cout << "a + b = " << (a + b).str() << "\n";
    std::cout << "a - b = " << (a - b).str() << "\n";
    std::cout << "a * b = " << (a * b).str() << "\n";
    std::cout << "a / b = " << (a / b).str() << "\n";

    std::cout << "double(a) = " << (double)a << "\n";
}
