#include <iostream>
#include <string>
#include "nodes.h"

using namespace std;

extern FILE* yyin;
extern int yyparse();

int main() {

    string filename;
    cin >> filename;

    yyin = fopen(filename.c_str(), "r");

    if (yyparse() == 0) {
        cout << "EOF\n";
    } 

    fclose(yyin);
    return 0;
}