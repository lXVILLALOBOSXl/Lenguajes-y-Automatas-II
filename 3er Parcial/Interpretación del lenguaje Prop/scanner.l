%{

#include "nodes.h"
#include "parser.hpp"

extern "C" int yywrap();
extern YYSTYPE yylval;  

int line = 1;

%}


id      [a-z][a-z0-9']*
wsp     [ \t]
nline   \n

%%


"true"             { yylval.p = new_const(true); return TRUE; }
"false"            { yylval.p = new_const(false); return FALSE; }

"not"              { return NOT; }
"and"              { return AND; }
"or"               { return OR; }

"->"               { return IMPLIES; }
"="                { return EQ; }
"!="               { return NEQ; }

"?"                { return QMARK; }
":"                { return COLON; }
";"                { return SEMI; }
"<<"               { return PRINT; }

"("                { return LPAREN; }
")"                { return RPAREN; }

{id}               { yylval.p = new_id(yytext); return ID; }

{wsp}    ;
{nline}  line++;

.        return -1;

<<eof>> return 0;

%%

int yywrap() {  return 1; }