%{

#include "parser.hpp"

extern "C" int yywrap();
extern YYSTYPE yylval;  

int line = 1;

%}


number  0|[1-9][0-9]*
    // id      [a-z]+
ops     [-+*/]
sep     [()] 
punct   [:;]

wsp     [ \t]
nline   \n

%%

    // {id}     return id;

{number} { yylval.value = atof(yytext);
           return num;
         }
{ops}    return *yytext;
{sep}    return *yytext;
{punct}  return *yytext;

{wsp}    ;
{nline}  line++;

.        return -1;

<<eof>> return 0;

%%

int yywrap() {  return 1; }