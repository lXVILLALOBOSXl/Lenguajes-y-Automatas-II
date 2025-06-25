%{

#include <stdio.h>
#include "nodes.h"

int yyerror(const char *);

extern int yylex();
extern int line;

node *tree = NULL;

%}

%union {
  node *p;
  float value;
}

  // Declaracion de simbolos gramaticales

%token <value> num

  //%token id

%type <p> exp
%type <p> term
%type <p> factor

%%

  // Declaracion de la gramatica

  // assignlist: assign | assignlist assign ;
  // assign:     id ':' exp ';' ;
start: exp { tree = $1; };

exp:       

        exp '+' term { $$ = newnode(sum, $1, $3); }
      | exp '-' term { $$ = newnode(diff, $1, $3); }
      | term { $$ = $1; }
      ;

term:  

        term '*' factor { $$ = newnode(mult, $1, $3); }
      | term '/' factor { $$ = newnode(_div, $1, $3); }
      | factor { $$ = $1; }
      ;

factor:     

        '(' exp ')' { $$ = $2; }
      | '-' factor { $$ = newnode($2); }
      | num { $$ = newnode($1); }
      ;

      // factor:     '(' exp ')' | '-' factor | num | id ;


%%

// Numeric node
extern node *newnode(float x){

  node *p = new node;

  p -> type = numeric;
  p -> value = x;

  p -> left = NULL;
  p -> right = NULL;

  return p;

}

// Atomic node (negation)
extern node *newnode(node *q){

  node *p = new node;

  p -> type = neg;
  p -> value = 0.0;

  p -> left = q;
  p -> right = NULL;

  return p;

}

// Binary node
extern node *newnode(tnode t, node *l, node *r){
  node *p = new node;

  p -> type = t;
  p -> value = 0.0;

  p -> left = l;
  p -> right = r;

  return p;
}

int yyerror(const char *mssg) {

    printf("[%i] %s\n", line, mssg);
    return 0;
}