%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

extern int alpha_yylex(Token *token);
Token t;

int yylex(void) {
	if(alpha_yylex(&t)) {
		return 1; /* generic token */
	}
	return 0;
}

void yyerror(const char *s);
%}

%token STRING
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS DOUBLE_COLON DOUBLE_DOT COLON DOT COMMA SEMI_COLON
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token EQUAL NOT_EQUAL LESS_EQUAL GREATER_EQUAL ASSIGN LESS GREATER PLUS_PLUS PLUS MINUS_MINUS MINUS MULTIPLY DIVISION MOD
%token CONST_INT CONST_REAL
%token ID

%%

program:
       statement
;

statement:
	 stmt statement | /* empty */

stmt:
    expr SEMI_COLON | ifstmt | whilestmt | forstmt | returnstmt | BREAK SEMI_COLON | CONTINUE SEMI_COLON | block | funcdef | SEMI_COLON
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
      ID | LOCAL ID | DOUBLE_COLON ID | member
;

member:
      lvalue DOT ID | lvalue LEFT_BRACKET expr RIGHT_BRACKET | call DOT ID | call LEFT_BRACKET expr RIGHT_BRACKET
;

call:
    call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS | lvalue callsuffix | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
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
     LEFT_BRACE stmt RIGHT_BRACE
;

funcdef:
       FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block
;

const:
     CONST_INT | CONST_REAL | STRING | NIL | TRUE | FALSE
;

idlist:
      ID | idlist COMMA ID
;

ifstmt:
	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt elsestmt
;

elsestmt:
	ELSE stmt | /* empty */
;

whilestmt:
	 WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt
;

forstmt:
       FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS stmt
;

returnstmt:
	  RETURN returnvalue SEMI_COLON
;

returnvalue:
	   expr | /* empty */
;

%%

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

