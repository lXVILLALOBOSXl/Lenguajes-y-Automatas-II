#include <iostream>
#include "parser.hpp"

int main(int argc, const char * argv[]) {
    
    
    parser p("/Users/luisvillalobos/Documents/Programacion/TECMM/Lenguajes y automatas II/2do Parcial/LL(1) Recursive/prueba.txt");

    if (p.parse()) std::cout << "Ok\n";
    else std::cout << "Error sintáctico\n";    
    
    return 0;
}