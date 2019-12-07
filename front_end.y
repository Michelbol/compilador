%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helpers.c"
#include "variables.c"
#include "binary_tree.c"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
	char *string;
	struct VARIABLE *variable;
}

%token<ival> T_INT
%token<fval> T_FLOAT
%token T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_EXP T_PLUS T_MINUS
%token T_NEWLINE T_COMMA
%token <string> IDENTIFIER
%token T_QUIT PRINT ATTR
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<ival> expression
%type<fval> mixed_expression

%start calculation

%%

calculation:
	   | calculation line
;

line: T_NEWLINE
    | T_QUIT T_NEWLINE { printf("bye!\n"); exit(0); } 				// exit
    | PRINT mixed_expression T_NEWLINE { createNodePrintFloat(&$2); } 			// print float
    | PRINT expression T_NEWLINE { createNodePrintInt(&$2); }			// print int
    | PRINT IDENTIFIER T_NEWLINE { findAndPrintVariable($2); }			// print variable
    | IDENTIFIER ATTR expression T_NEWLINE { insertVariable($1, $3); }		// variable = int
    | IDENTIFIER ATTR mixed_expression T_NEWLINE { insertVariableF($1, $3); }	// variable = float
    | expression T_NEWLINE { printf("result: %i\n", $1);}
    | IDENTIFIER ATTR mixed_expression T_NEWLINE { insertVariableF($1, $3); }	// variable = float
;

mixed_expression: T_FLOAT                 		 { $$ = $1; }
	  | mixed_expression T_PLUS mixed_expression	 { $$ = $1 + $3; }	// Soma de floats
	  | mixed_expression T_MINUS mixed_expression	 { $$ = $1 - $3; }	// subtração de floats
	  | mixed_expression T_MULTIPLY mixed_expression { $$ = $1 * $3; }	// multiplicação de floats
	  | mixed_expression T_DIVIDE mixed_expression	 { $$ = $1 / $3; }	// divisão de floats
	  | mixed_expression T_EXP mixed_expression	 { $$ = pow($1, $3); }	// exponenciação de floats
	  | T_LEFT mixed_expression T_RIGHT		 { $$ = $2; }		// (float)
	  | expression T_DIVIDE expression		 { $$ = (float)$1 / (float)$3; } 	//int / int
	  | IDENTIFIER T_DIVIDE expression		 { $$ = findVariableList($1)->intVal / $3; } //variable / int
	  | expression T_DIVIDE IDENTIFIER		 { $$ = $1 / findVariableList($3)->intVal; } // int / variable
	  | expression T_PLUS mixed_expression { printf("Impossível, número inteiro + número float"); }	// int + float -> erro
      	  | expression T_MINUS mixed_expression { printf("Impossível, número inteiro - número float"); }	// int - float -> erro
      	  | expression T_MULTIPLY mixed_expression { printf("Impossível, número inteiro * número float"); }	// int * float -> erro
      	  | expression T_DIVIDE mixed_expression { printf("Impossível, número inteiro / número float"); }	// int / float -> erro
      	  | expression T_EXP mixed_expression { printf("Impossível, número inteiro ^ número float"); }	// int ^ float -> erro
      	  | mixed_expression T_PLUS expression { printf("Impossível, número float + número inteiro"); }	// float + int -> erro
      	  | mixed_expression T_MINUS expression { printf("Impossível, número float - número inteiro"); }	// float - int -> erro
      	  | mixed_expression T_MULTIPLY expression { printf("Impossível, número float * número inteiro"); }	// float * int -> erro
      	  | mixed_expression T_DIVIDE expression { printf("Impossível, número float / número inteiro"); }	// float / int -> erro
      	  | mixed_expression T_EXP expression { printf("Impossível, número float ^ número inteiro"); }	// float ^ int -> erro
;

expression: T_INT				{ $$ = $1; }
	  | expression T_PLUS expression	{ $$ = createNodeSumInt($1, $3); }		// int + int
	  | expression T_MINUS expression	{ $$ = $1 - $3; }		// int - int
	  | expression T_MULTIPLY expression	{ $$ = $1 * $3; }		// int * int
	  | expression T_EXP expression		{ $$ = pow($1, $3); }		// int ^ int
	  | T_LEFT expression T_RIGHT		{ $$ = $2; }			// (int)
	  | IDENTIFIER T_PLUS expression	{ $$ = findVariableList($1)->intVal + $3; }		// int + int
	  | IDENTIFIER T_MINUS expression	{ $$ = findVariableList($1)->intVal - $3; }		// int - int
	  | IDENTIFIER T_MULTIPLY expression	{ $$ = findVariableList($1)->intVal * $3; }		// int * int
	  | IDENTIFIER T_EXP expression		{ $$ = pow(findVariableList($1)->intVal, $3); }		// int ^ int
	  | expression T_PLUS IDENTIFIER	{ $$ = $1 + findVariableList($3)->intVal; }		// int + int
	  | expression T_MINUS IDENTIFIER 	{ $$ = $1 - findVariableList($3)->intVal; }		// int - int
	  | expression T_MULTIPLY IDENTIFIER 	{ $$ = $1 * findVariableList($3)->intVal; }		// int * int
	  | expression T_EXP IDENTIFIER 	{ $$ = pow($1, findVariableList($3)->intVal); }		// int ^ int
;

%%

int main(int argc, char *argv[]) {
	startList();

	char *file_name = "calculator.txt";
	FILE *f = fopen(file_name, "r");

	startTree();
	yyin = f;

	yyparse();

	execute();
	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}