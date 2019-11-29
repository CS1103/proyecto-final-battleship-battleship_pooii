#include <iostream>
#include <fstream>

#include "funct.hpp"
#include "prettyprint.hpp"

int main()
{
    std::ifstream archivo("texto.txt");
    auto valores = read(archivo);
    parse(valores);
    
}
