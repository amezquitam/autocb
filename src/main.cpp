#include "trigonometric.hpp"
#include <iostream>

int main() {
    std::string entry;
    
    std::cout << "Input: ";
    std::getline(std::cin, entry);

    std::cout << std::boolalpha;
    std::cout << "Is trigonometric?: " << is_trigonometric(entry.c_str()) << '\n';

    std::cin.get();
}