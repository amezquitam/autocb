#include "trigonometric.hpp"
#include <iostream>

int main() {
    std::string entry;
    
    std::cout << "Input: ";
    std::getline(std::cin, entry);

    std::cout << std::boolalpha;

    auto [is_trig, value] = is_trigonometric(entry.c_str());

    std::cout << "Is trigonometric?: " << is_trig << '\n';
    std::cout << "Evaluated: " << value << '\n';

    std::cin.get();
}