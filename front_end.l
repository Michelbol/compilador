%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

#include "front_end.tab.h"

%}

%%
"print"		{return PRINT;}
"quit"		{return T_QUIT;}
[a-zA-Z]+ { yylval.string = strdup(yytext); return IDENTIFIER;}
[ \t]+
[0-9]+\.[0-9]+ 	{yylval.fval = atof(yytext); return T_FLOAT;}
[0-9]+		{yylval.ival = atoi(yytext); return T_INT;}

"\n"	{return T_NEWLINE;}
","     {return T_COMMA;}
"+"		{return T_PLUS;}
"-"		{return T_MINUS;}
"*"		{return T_MULTIPLY;}
"="		{return ATTR;}
"/"		{return T_DIVIDE;}
"("		{return T_LEFT;}
")"		{return T_RIGHT;}
"^"     {return T_EXP;}

%%