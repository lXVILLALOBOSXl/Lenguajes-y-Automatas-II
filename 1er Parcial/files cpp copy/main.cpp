#include <iostream>
#include "scanner.hpp"

int main(int argc, const char * argv[]) {
    
    scanner s("/Users/luisvillalobos/Documents/Programacion/TECMM/Lenguajes y automatas II/1er Parcial/files cpp copy/prueba.txt");
    
    scanner::token t;

    do
    {
        t = s.next();

        switch (t) {
            case scanner::integer:
                cout << "Integer" << endl;
                break;
            case scanner::real:
                cout << "Real" << endl;
                break;
            case scanner::identif:
                cout << "Identif" << endl;
                break;
            case scanner::_eof:
                cout << "EOF" << endl;
                break;
            case scanner::err:
                cout << "Error" << endl;
        }
    } while (t != scanner::err && t != scanner::_eof);


    cout << "Gracias por trabajar conmigo\n";
    
    
    return 0;
}