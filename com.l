%{
#include "com.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

digit    [0-9]
letter   [a-z]
sep      [ \t\n\r]

%%

"("              { return LPAREN; }
")"              { return RPAREN; }
"+"              { return PLUS; }
"-"              { return MINUS; }
"*"              { return MULTIPLY; }
"/"              { return DIVIDE; }
"mod"            { return MODULUS; }
">"              { return GREATER; }
"<"              { return SMALLER; }
"="              { return EQUAL; }
"and"            { return AND; }
"or"             { return OR; }
"not"            { return NOT; }
"define"         { return DEFINE; }
"fun"            { return FUN; }
"if"             { return IF; }
"print-num"      { return PRINT_NUM; }
"print-bool"     { return PRINT_BOOL; }

"#t"             { yylval.num = 1; return BOOL_VAL; }
"#f"             { yylval.num = 0; return BOOL_VAL; }

{digit}+         { yylval.num = atoi(yytext); return NUMBER; }
-({digit}+|{digit}*) { yylval.num = atoi(yytext); return NUMBER; }
{letter}({letter}|{digit}|"-")* { yylval.str = strdup(yytext); return ID; }

{sep}+           { /* Ignore separators */ }
.                { printf("Unknown character: %s\n", yytext); exit(1); }

%%

