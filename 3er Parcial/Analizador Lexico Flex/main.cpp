#include <iostream>

using namespace std;

extern FILE *yyin;
extern int yylex();
extern char* yytext;
extern int line;

int main(int argc, const char * argv[]) {

    string file_name;
    cin >> file_name;

    yyin = fopen(file_name.c_str(), "r");

    if (yyin == NULL) {
        cout << "Error abriendo archivo" << endl;
        return 1;
    }

    int token = 1;
    while (token  != 0 and token != -1){
        token = yylex();
        switch (token) {
            case 1: cout << "Identificador: " << yytext << endl; break;
            case 2: cout << "Octal: " << yytext << endl; break;
            case 3: cout << "Hexadecimal: " << yytext << endl; break;
            case 4: cout << "Integer: " << yytext << endl; break;
            case 5: cout << "Real: " << yytext << endl; break;
            case 6: cout << "Operador: " << yytext << endl; break;
            case 7: cout << "Delimitador: " << yytext << endl; break;
            case 8: cout << "Puntuación: " << yytext << endl; break;
            case 10: cout << "Reservada: " << yytext << endl; break;
            case 11: cout << "Comentario: " << yytext << endl; break;
        }

    }

    if (token == -1){
        cout << "Error en linea " << line << endl;
    }else{
        cout << "Fin del análisis, " << line << " líneas analizadas" << endl;
    }



    fclose(yyin);
    return 0;
}