#include <iostream>
#include "scanner.hpp"

int main(int argc, const char * argv[]) {

    // parser p("/Users/luisvillalobos/Documents/Programacion/TECMM/Lenguajes y automatas II/3er Parcial/SLR(1) Controller/prueba.txt");

    // if (p.parse()) std::cout << "Ok\n";
    // else std::cout << "Error sintáctico\n";    
    
    // string file_name;
    // cin >> file_name;

    string file_name = "/Users/luisvillalobos/Documents/Programacion/TECMM/Lenguajes y automatas II/3er Parcial/SLR(1) Controller/prueba.txt";

    scanner s(file_name);

    scanner::token t;

    

    do
    {
        t = s.next();

        switch (t) {
            case scanner::_identif:
                std::cout << "Terminal id: " << s.get_lexeme() << "\n";
                break;
            case scanner::_question_mark:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;  
            case scanner::_dots:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::_or:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::_and:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::_not:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::lpar:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::rpar:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::_false:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::_true:
                std::cout << "Terminal: " << s.get_lexeme() << "\n";
                break;
            case scanner::tab:
                std::cout << "Tabulador\n";
                break;
            case scanner::_enter:
                std::cout << "Enter\n";
                break;
            case scanner::whitespace:
                std::cout << "Espacio en blanco\n";
                break;
            case scanner::_eof:
                std::cout << "Fin de archivo\n";
                break;
            case scanner::err:
                cout << "Error en la linea " << s.get_line() << endl;
                break;
        }
    } while (t != scanner::err && t != scanner::_eof);
    
    return 0;
}