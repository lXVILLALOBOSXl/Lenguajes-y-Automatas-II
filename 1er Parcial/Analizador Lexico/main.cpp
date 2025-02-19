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
            case scanner::reserved:
                cout << "Reserved: " << s.get_lexeme() << endl;
                break;
            case scanner::delimiter:
                cout << "Delimiter" << endl;
                break;
            case scanner::punctuation:
                cout << "Punctuation" << endl;
                break;
            case scanner::operators:
                cout << "Operator" << endl;
                break;
            case scanner::whitespace:
                cout << "Whitespace" << endl;
                break;
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