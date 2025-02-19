%{
# include "scanner.h"

int line = 1;
%}

hex   [0-9a-fA-F]
N     [0-9]
A     [a-zA-Z]
sub   -

hexnum 0(x|X)({hex}{2})+
id     ({A}|{sub}({sub}|{N})*{A})({A}|{N}|{sub})*
sp     [ \t]
nl     \n

%%

{hexnum} return _hex;
{id}     return _id;
{sp}     ;
{nl}     line++;
.        printf("Line %i: Error[%c]\n", line, **yytext);

<<EOF>>  return _eof;

%%

int yywrap() { return 1; }