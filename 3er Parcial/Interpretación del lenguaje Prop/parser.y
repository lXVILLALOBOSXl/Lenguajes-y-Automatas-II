%{

#include <iostream>
#include <map>
#include <string>
#include "nodes.h"

using namespace std;

int yyerror(const char *);

extern int yylex();
extern int line;

map<string, bool> memory;

void eval_and_print(node*);
bool eval(node*);

node *tree = NULL;

%}

%union {
  node *p;
  float value;
}

  // Declaracion de simbolos gramaticales

%token <p> TRUE FALSE ID
%token NOT AND OR IMPLIES EQ NEQ QMARK COLON SEMI PRINT LPAREN RPAREN

%type <p> start stseq st assign output quest argue prop clause equiv atom
  //%token id

%left OR
%left AND
%right IMPLIES
%left EQ NEQ
%right QMARK COLON
%right NOT



%%

start
    : stseq
    | stseq SEMI
    ;

stseq
    : stseq SEMI st
    | st
    ;

st
    : assign
    | output
    ;

assign
    : ID COLON quest {
        bool val = eval($3);
        memory[$1->id] = val;
      }
    ;

output
    : PRINT quest {
        eval_and_print($2);
      }
    ;

quest
    : argue QMARK quest COLON quest { $$ = new_ternary(t_select, $1, $3, $5); }
    | argue                         { $$ = $1; }
    ;

argue
    : prop IMPLIES prop { $$ = new_binary(t_implies, $1, $3); }
    | prop              { $$ = $1; }
    ;

prop
    : prop OR clause { $$ = new_binary(t_or, $1, $3); }
    | clause         { $$ = $1; }
    ;

clause
    : clause AND equiv { $$ = new_binary(t_and, $1, $3); }
    | equiv            { $$ = $1; }
    ;

equiv
    : atom EQ atom  { $$ = new_binary(t_eq, $1, $3); }
    | atom NEQ atom { $$ = new_binary(t_neq, $1, $3); }
    | atom          { $$ = $1; }
    ;

atom
    : NOT atom           { $$ = new_unary(t_not, $2); }
    | LPAREN quest RPAREN { $$ = $2; }
    | ID                 {
                            if (memory.find($1->id) == memory.end()) {
                              cout << "Line " << line << ": Undefined variable\n";
                              YYABORT;
                            }
                            $1->value = memory[$1->id];
                            $$ = $1;
                          }
    | FALSE              { $$ = $1; }
    | TRUE               { $$ = $1; }
    ;

%%

// Constante
extern node* new_const(bool value) {
    node* p = new node;
    p->type = t_const;
    p->value = value;
    p->id = "";
    p->left = NULL;
    p->middle = NULL;
    p->right = NULL;
    return p;
}

// ID
extern node* new_id(const string& name) {
    node* p = new node;
    p->type = t_id;
    p->value = false;
    p->id = name;
    p->left = NULL;
    p->middle = NULL;
    p->right = NULL;
    return p;
}

// Not
extern node* new_unary(tnode t, node* child) {
    node* p = new node;
    p->type = t;
    p->value = false;
    p->id = "";
    p->left = child;
    p->middle = NULL;
    p->right = NULL;
    return p;
}

// Operadores binarios
extern node* new_binary(tnode t, node* left, node* right) {
    node* p = new node;
    p->type = t;
    p->value = false;
    p->id = "";
    p->left = left;
    p->middle = NULL;
    p->right = right;
    return p;
}

// Operador ternario
extern node* new_ternary(tnode t, node* cond, node* then_expr, node* else_expr) {
    node* p = new node;
    p->type = t;
    p->value = false;
    p->id = "";
    p->left = cond;
    p->middle = then_expr;
    p->right = else_expr;
    return p;
}

bool eval(node* n) {
    switch (n->type) {
        case t_const:
            return n->value;
        case t_id:
            return n->value;
        case t_not:
            return !eval(n->left);
        case t_and:
            return eval(n->left) && eval(n->right);
        case t_or:
            return eval(n->left) || eval(n->right);
        case t_implies:
            return !eval(n->left) || eval(n->right);
        case t_eq:
            return eval(n->left) == eval(n->right);
        case t_neq:
            return eval(n->left) != eval(n->right);
        case t_select:
            return eval(n->left) ? eval(n->middle) : eval(n->right);
        default:
            cout << "Invalid operation\n";
            exit(1);
    }
}

void eval_and_print(node* n) {
    bool result = eval(n);
    cout << (result ? "true" : "false") << endl;
}

int yyerror(const char *msg) {
    cout << "Line" << line << ": " << msg << endl;
    return 0;
}