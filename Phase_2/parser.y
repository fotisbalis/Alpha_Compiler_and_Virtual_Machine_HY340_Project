%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "token.h"
#include "symbol_table.h"

extern FILE *yyin;
extern int alpha_yylex(Token *token);
Token t;

SymTable_T sym_table;
int current_scope = 0, loop_depth = 0, function_depth = 0;
char* current_lvalue = NULL;

int yylex(void) {
	return alpha_yylex(&t);
}

void yyerror(const char *s);
%}

%union {
	char* strVal;
	char* idVal;
	int intVal;
	double realVal;
}

%token LINE_COMMENT NESTED_COMMENT BLOCK_COMMENT
%token <strVal> STRING
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS DOUBLE_COLON DOUBLE_DOT COLON DOT COMMA SEMI_COLON
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token EQUAL NOT_EQUAL LESS_EQUAL GREATER_EQUAL ASSIGN LESS GREATER PLUS_PLUS PLUS MINUS_MINUS MINUS MULTIPLY DIVISION MOD
%token <intVal> CONST_INT 
%token <realVal> CONST_REAL
%token <idVal> ID

%%

program:
       statement
;

statement:
	 stmt statement | LINE_COMMENT statement | BLOCK_COMMENT statement | /* empty */

stmt:
	expr SEMI_COLON | ifstmt | whilestmt | forstmt | returnstmt
	| BREAK SEMI_COLON {
		if(loop_depth == 0) printf("Error: break called outside of loop at line %d\n", t.line);	
	}
	| CONTINUE SEMI_COLON {
                if(loop_depth == 0) printf("Error: continue called outside of loop at line %d\n", t.line);
	}
	| block | funcdef | SEMI_COLON
;

expr:
    assignexpr | expr op expr | term
;

op:
  PLUS | MINUS | MULTIPLY | DIVISION | MOD | GREATER | GREATER_EQUAL | LESS | LESS_EQUAL | EQUAL | NOT_EQUAL | AND | OR
;

term:
    LEFT_PARENTHESIS expr RIGHT_PARENTHESIS | MINUS expr | NOT expr | PLUS_PLUS lvalue | lvalue PLUS_PLUS | MINUS_MINUS lvalue | lvalue MINUS_MINUS | primary
;

assignexpr:
	  lvalue ASSIGN expr
;

primary:
       lvalue | call | objectdef | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS | const
;

lvalue:
	ID { /* add in current scope */
		current_lvalue = $1;

		if(SymTable_lookup_scope(sym_table, $1, current_scope) == NULL){
			Symbol* s = Symbol_create($1, "variable", current_scope, t.line, 1);
            		SymTable_put(sym_table, s);
		}
	}
	| LOCAL ID { /* check for declaration then add */
		current_lvalue = $2;

		Symbol* s = SymTable_lookup_scope(sym_table, $2, current_scope);
                
		if(s != NULL){
                        printf("Error: redeclaration of local variable %s at line %d\n", $2, t.line);
                }

                else {
                        Symbol* new_s = Symbol_create($2, "local variable", current_scope, t.line, 1);
                        SymTable_put(sym_table, new_s);
                }
        } 
	| DOUBLE_COLON ID { /* lookup in scope 0 */
		current_lvalue = $2;

		Symbol* s = SymTable_lookup_scope(sym_table, $2, 0);

		if(s == NULL){
			printf("Error: undefined global variable %s at line %d\n", $2, t.line);
		}
	}
	| member
;

member:
      lvalue DOT ID | lvalue LEFT_BRACKET expr RIGHT_BRACKET | call DOT ID | call LEFT_BRACKET expr RIGHT_BRACKET
;

call:
    call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
    | lvalue callsuffix { /* check if symbol used as function is in the symbol table and if it is a function */
	Symbol* s = SymTable_lookup(sym_table, current_lvalue, current_scope);

	if(s == NULL){
        	printf("Error: undefined function %s at line %d\n", current_lvalue, t.line);
	}

	if(strcmp(s->type, "function") != 0){
		printf("Error: %s %s incorrectly used as function at line %d\n", s->type, current_lvalue, t.line);
    
	}
    }
    | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
;

callsuffix:
	  normcall | methodcall
;

normcall:
	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
;

methodcall:
	  DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
;

elist:
     expr | elist COMMA expr 
;

objectdef:
	 LEFT_BRACKET obj RIGHT_BRACKET
;

obj:
   elist | indexed
;

indexed:
       indexedelem | indexed COMMA indexedelem
;

indexedelem:
	   LEFT_BRACE expr COLON expr RIGHT_BRACE
;

block:
	LEFT_BRACE {
		current_scope++;
	} 	
	stmt 
	RIGHT_BRACE {	
		SymTable_hide_scope(sym_table, current_scope); 
		current_scope--;
	}
;

funcdef:
       FUNCTION ID {
		if(SymTable_lookup_scope(sym_table, $2, current_scope) == NULL){
			Symbol* s = Symbol_create($2, "function", current_scope, t.line, 1);
			SymTable_put(sym_table, s);
			current_scope++;
                	function_depth++;
		}
		else {
			printf("Error: redeclaration of function %s at line %d\n", $2, t.line);
		}
	}
	LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS 
	block {
		SymTable_hide_scope(sym_table, current_scope);
		current_scope--;
		function_depth--;
	}
;

const:
     CONST_INT | CONST_REAL | STRING | NIL | TRUE | FALSE
;

idlist:
	ID { 	
		if(SymTable_lookup_scope(sym_table, $1, current_scope) == NULL){
			Symbol* s = Symbol_create($1, "parameter", current_scope, t.line, 1);
           		SymTable_put(sym_table, s); 
		}
	}
	| idlist COMMA ID {
		if(SymTable_lookup_scope(sym_table, $3, current_scope) == NULL){
			Symbol* s = Symbol_create($3, "parameter", current_scope, t.line, 1);
                	SymTable_put(sym_table, s);
		}
        }
	| /* empty */
;

ifstmt:
	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt elsestmt
;

elsestmt:
	ELSE stmt | /* empty */
;

whilestmt:
	 WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
        { loop_depth++; }
        stmt
        { loop_depth--; }
;

forstmt:
	FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS 
	{ loop_depth++; }
	stmt
	{ loop_depth--; }
;

returnstmt:
	  RETURN returnvalue SEMI_COLON 
	{ if(function_depth == 0) printf("Error: return called outside of function at line %d\n", t.line); }
;

returnvalue:
	   expr | /* empty */
;

%%

int main(int argc, char **argv) {
	
	assert(argc == 2);

	yyin = fopen(argv[1], "r");
	assert(yyin);

	printf("Parsing started.\n");

	sym_table = SymTable_create();
	
	if(yyparse() != 0) {
        	SymTable_free(sym_table);
        	return 1;
    	}	

    	printf("Parsing finished.\n");

	SymTable_print(sym_table);

	SymTable_free(sym_table);
	fclose(yyin);
    	
	return 0;
}

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

