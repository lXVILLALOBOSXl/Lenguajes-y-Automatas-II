%{

#include <stdio.h>

int yyerror(const char *);

extern int yylex();
extern int line;

%}

%union {
     float value;
}

  // Declaracion de simbolos gramaticales

%token <value> num

  //%token id

%type <value> exp
%type <value> term
%type <value> factor

%%

  // Declaracion de la gramatica

  // assignlist: assign | assignlist assign ;
  // assign:     id ':' exp ';' ;
start: exp { printf("Resultado: %f\n", $1); };

exp:       

        exp '+' term { $$ = $1 + $3; }
      | exp '-' term { $$ = $1 - $3; }
      | term { $$ = $1; }
      ;

term:  

        term '*' factor { $$ = $1 * $3; }
      | term '/' factor { $$ = $1 / $3; }
      | factor { $$ = $1; }
      ;

factor:     

        '(' exp ')' { $$ = $2; }
      | '-' factor { $$ = -$2; }
      | num { $$ = $1; }
      ;

      // factor:     '(' exp ')' | '-' factor | num | id ;


%%

int yyerror(const char *mssg) {

    printf("[%i] %s\n", line, mssg);
    return 0;
}