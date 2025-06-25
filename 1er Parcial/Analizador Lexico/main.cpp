#include <iostream>
#include "scanner.hpp"

int main(int argc, const char * argv[]) {


    string file_name;
    cin >> file_name;
    
    scanner s(file_name);

    scanner::token t;

    do
    {
        t = s.next();

        switch (t) {
            case scanner::integer:
                cout << "Integer: " << s.get_lexeme() << endl;
                break;
            case scanner::real:
                cout << "Real: " << s.get_lexeme() << endl;
                break;
            case scanner::oct:
                cout << "Octal: " << s.get_lexeme() << endl;
                break;
            case scanner::hex:
                cout << "Hexadecimal: " << s.get_lexeme() << endl;
                break;
            case scanner::identif:
                cout << "Identificator: " << s.get_lexeme() << endl;
                break;
            case scanner::_true:
                cout << "true: " << s.get_lexeme() << endl;
                break;
            case scanner::_false:
                cout << "false: " << s.get_lexeme() << endl;
                break;
            case scanner::_print:
                cout << "print: " << s.get_lexeme() << endl;
                break;
            case scanner::lbra:
                cout << "Left bracket: " << s.get_lexeme() << endl;
                break;
            case scanner::rbra:
                cout << "Right bracket: " << s.get_lexeme() << endl;
                break;
            case scanner::lpar:
                cout << "Left parenthesis: " << s.get_lexeme() << endl;
                break;
            case scanner::rpar:
                cout << "Right parenthesis: " << s.get_lexeme() << endl;
                break;
            case scanner::_point:
                cout << "Dot: " << s.get_lexeme() << endl;
                break;
            case scanner::_comma:
                cout << "Comma: " << s.get_lexeme() << endl;
                break;
            case scanner::_pandcomma:
                cout << "Point and comma: " << s.get_lexeme() << endl;
                break;
            case scanner::dots:
                cout << "Dots: " << s.get_lexeme() << endl;
                break;
            case scanner::ampersand:
                cout << "Ampersand: " << s.get_lexeme() << endl;
                break;
            case scanner::bar:
                cout << "Bar: " << s.get_lexeme() << endl;
                break;
            case scanner::excla:
                cout << "Exclamation: " << s.get_lexeme() << endl;
                break;
            case scanner::arrow:
                cout << "Arrow: " << s.get_lexeme() << endl;
                break;
            // case scanner::_comment:
            //     cout << "Comment: " << s.get_lexeme() << endl;
            //     break;
            case scanner::_eof:
                cout << "Fin del analisis, "<<s.get_line()<<" lineas analizadas" << endl; 
                break;
            case scanner::err:
                cout << "Error en la linea " << s.get_line() << endl;
                break;
        }
    } while (t != scanner::err && t != scanner::_eof);


    
    
    return 0;
}