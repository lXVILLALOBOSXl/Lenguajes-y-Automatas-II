%{
extern "C" int yywrap();
int line = 1;
extern char* yytext;
%}

id             [_]*[a-zA-Z]+[a-zA-Z0-9_]*
reserved       print|true|false

octal          0[0-7]+
hex            0[xX]([0-9a-fA-F]{2})+
real           0\.[0-9]+|[1-9][0-9]*\.[0-9]+
integer        [1-9][0-9]*

comment        \#.*

delim          [()\[\]]
punct          [.,;]
op_imp         "->"
op_single      [:&|!\-]

space          [ \t]+
newline        \n

%%

{reserved}      { return 10; }
{id}            { return 1; }
{octal}         { return 2; }
{hex}           { return 3; }
[0-9]+[a-zA-Z_][a-zA-Z0-9_]*   { return -1; }
{real}          { return 5; }
{integer}       { return 4; }

{op_imp}        { return 6; }
{op_single}     { return 6; }
{delim}         { return 7; }
{punct}         { return 8; }

{comment}       { return 11; }
{space}         ; 
{newline}       { line++; }

.               { return -1; }

<<EOF>>         { return 0; }

%%

int yywrap() { return 1; }