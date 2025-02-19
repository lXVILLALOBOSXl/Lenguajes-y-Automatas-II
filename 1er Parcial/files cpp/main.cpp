#include <iostream>
#include "scanner.hpp"

int main(int argc, const char * argv[]) {
    
    scanner s("/Users/luisvillalobos/Documents/Programacion/TECMM/Lenguajes y automatas II/1er Parcial/files cpp/prueba.txt");
    
    if (s.next()) cout << "Si jala\n" << endl;
    else cout << "No jala\n" << endl;
    
    return 0;
}