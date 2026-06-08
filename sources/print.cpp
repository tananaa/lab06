#include "print.hpp"
#include <fstream>
#include <iostream>

void print(const std::string& text) {
    std::cout << text << std::endl;
}

void print(const std::string& text, std::ostream& out) {
    out << text << std::endl;
}

void print(const std::string& text, const std::string& filename) {
    std::ofstream out(filename);
    out << text << std::endl;
}
