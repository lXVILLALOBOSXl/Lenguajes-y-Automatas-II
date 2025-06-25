#include <iostream>

extern FILE *yyin; // File for Flex
extern int yyparse(); // Parser


int main(int argc, const char * argv[]) {
    
    yyin = fopen("test.txt", "r");

    if (yyparse() == 0) printf("Ok\n");
    else printf("Error\n");

    fclose(yyin);
    
    
    return 0;
}