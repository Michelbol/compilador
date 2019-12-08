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
	struct TREE *tree;
}

%token<ival> T_INT
%token<fval> T_FLOAT
%token T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_EXP T_PLUS T_MINUS
%token T_NEWLINE T_COMMA
%token <string> IDENTIFIER
%token T_QUIT PRINT ATTR
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<tree> expression
%type<tree> mixed_expression

%start calculation

%%

calculation:
	   | calculation line
;

line: T_NEWLINE
	| PRINT expression T_NEWLINE { createNodePrintInt($2); }		// print int
	| PRINT mixed_expression T_NEWLINE { createNodePrintFloat($2); }	// print float
;

mixed_expression: T_FLOAT	{ $$ = createNodeFloat(&$1); }
;


expression: T_INT { $$ = createNodeInt(&$1); }
	| expression T_PLUS expression { $$ = createNodeSumInt($1, $3); }		// int + int
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