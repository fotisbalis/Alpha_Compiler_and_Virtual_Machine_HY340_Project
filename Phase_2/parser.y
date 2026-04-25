%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "token.h"
#include "symbol_table.h"
#include "error.h"

extern FILE *yyin;
extern int alpha_yylex(Token *token);
Token t;

SymTable_T sym_table;
int current_scope = 0, loop_depth = -1, function_depth = -1, function_scopes[100], function_started = 0;
Symbol* current_lvalue = NULL; 

void print_reduce(char *a, char* b){
	printf("%s -> %s\n", a, b);
}

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

%right ASSIGN

%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVISION MOD

%right NOT
%right UMINUS

%left DOT
%left LEFT_BRACKET RIGHT_BRACKET
%nonassoc IFX

%%

program:
       statements { print_reduce("program", "statements"); }
;

statements:
	/* empty */ { print_reduce("statements", "empty"); }
	| stmt statements { print_reduce("statements", "stmt statement"); } 
	| LINE_COMMENT statements { print_reduce("statements", "LINE_COMMENT statements"); }
	| BLOCK_COMMENT statements { print_reduce("statements", "BLOCK_COMMENT statements"); }

stmt:
	expr SEMI_COLON { print_reduce("stmt", "expr SEMI_COLON"); }
	| ifstmt { print_reduce("stmt", "ifstmt"); }
	| whilestmt { print_reduce("stmt", "whilestmt"); }
	| forstmt { print_reduce("stmt", "forstmt"); }
	| returnstmt { print_reduce("stmt", "returnstmt"); }
	| BREAK SEMI_COLON {
		if(loop_depth == -1){
			char error_message[200];
			sprintf(error_message, "ERROR: break called outside of loop at line %d", t.line);
			add_new_error(error_message);				
		}
		print_reduce("stmt", "returnstmt");
	}
	| CONTINUE SEMI_COLON {
                if(loop_depth == -1){
                        char error_message[200];
                        sprintf(error_message, "ERROR: continue called outside of loop at line %d", t.line);
                        add_new_error(error_message);
                }
		print_reduce("stmt", "CONTINUE SEMI_COLON");
	}
	| block { print_reduce("stmt", "block"); }
	| funcdef { print_reduce("stmt", "funcdef"); }
	| SEMI_COLON { print_reduce("stmt", "SEMI_COLON"); }
;

expr:
	assignexpr { print_reduce("expr", "assignexpr"); }
	| expr PLUS expr { print_reduce("expr", "expr PLUS expr"); }
	| expr MINUS expr { print_reduce("expr", "expr MINUS expr"); }
        | expr MULTIPLY expr { print_reduce("expr", "expr MULTIPLY expr"); }
        | expr DIVISION expr { print_reduce("expr", "expr DIVISION expr"); }
        | expr MOD expr { print_reduce("expr", "expr MOD expr"); }
        | expr GREATER expr { print_reduce("expr", "expr GREATER expr"); }
        | expr GREATER_EQUAL expr { print_reduce("expr", "expr GREATER_EQUAL expr"); }
        | expr LESS expr { print_reduce("expr", "expr LESS expr"); }
        | expr LESS_EQUAL expr { print_reduce("expr", "expr LESS_EQUAL expr"); }
        | expr EQUAL expr { print_reduce("expr", "expr EQUAL expr"); }
        | expr NOT_EQUAL expr { print_reduce("expr", "expr NOT_EQUAL expr"); }
        | expr AND expr { print_reduce("expr", "expr AND expr"); }
        | expr OR expr { print_reduce("expr", "expr OR expr"); }
	| term { print_reduce("expr", "term"); }
;

term:
    	LEFT_PARENTHESIS expr RIGHT_PARENTHESIS { print_reduce("term", "LEFT_PARENTHESIS expr RIGHT_PARENTHESIS"); }
	| MINUS expr %prec UMINUS { print_reduce("term", "MINUS expr"); }
	| NOT expr { print_reduce("term", "NOT expr"); }
	| PLUS_PLUS lvalue { print_reduce("term", "PLUS_PLUS lvalue"); }
	| lvalue PLUS_PLUS { print_reduce("term", "lvalue PLUS_PLUS"); }
	| MINUS_MINUS lvalue { print_reduce("term", "MINUS_MINUS lvalue"); }
	| lvalue MINUS_MINUS { print_reduce("term", "lvalue MINUS_MINUS"); }
	| primary { print_reduce("term", "primary"); }
;

assignexpr:
	lvalue ASSIGN expr { 
		if(current_lvalue != NULL){
			if(strcmp(current_lvalue->type, "function") == 0) {
                        	char error_message[200];
                        	sprintf(error_message, "ERROR: assign to function \"%s\" at line %d", current_lvalue->name, t.line);
                        	add_new_error(error_message);	
			}
		}

		print_reduce("assignexpr", "lvalue ASSIGN expr"); 
	}
;

primary:
       	lvalue { print_reduce("primary", "lvalue"); }
	| call { print_reduce("primary", "call"); }
	| objectdef { print_reduce("primary", "objectdef"); }
	| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS { print_reduce("primary", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS"); } 
	| const { print_reduce("primary", "const"); }
;

lvalue:
	ID { /* add in current scope */
		current_lvalue = NULL;
		Symbol *s = SymTable_lookup(sym_table, $1, current_scope, function_depth, function_scopes);
		Symbol* lib_check = SymTable_lookup_scope(sym_table, $1, 0);

		if(lib_check != NULL && strcmp(lib_check->type, "library function") == 0){
			char error_message[200];
                        sprintf(error_message, "ERROR: use of library function \"%s\" as variable at line %d", lib_check->name, t.line);
                        add_new_error(error_message);
                }

		else if(s == NULL){
			if(function_depth >= 0){
				if(function_depth > 0){
					int outer_scope = function_scopes[function_depth - 1];
					Symbol* outer_symbol = SymTable_lookup_scope(sym_table, $1, outer_scope);
				
					if(outer_symbol != NULL && strcmp(outer_symbol->type, "local variable") == 0){
						char error_message[200];
						sprintf(error_message, "ERROR: use of outer scope variable \"%s\" in nested function at line %d", $1, t.line);
						add_new_error(error_message);
					}
					else {
						s = Symbol_create($1, "local variable", current_scope, t.line, 1);
						SymTable_put(sym_table, s);
					}
				}
				else {
					s = Symbol_create($1, "local variable", current_scope, t.line, 1);
					SymTable_put(sym_table, s);
				}
			}
			else if(current_scope == 0){
                                s = Symbol_create($1, "global variable", current_scope, t.line, 1);
				SymTable_put(sym_table, s);
			}
                        else {
                                s = Symbol_create($1, "variable", current_scope, t.line, 1);		
				SymTable_put(sym_table, s);
			}
		}

		/* if its inside a function and not from function scope or a global variable, then error 
		else if(s != NULL && function_depth >= 0){
			int allowed = 0;

			if(s->scope == function_scopes[function_depth]) allowed = 1;

			else if(s->scope == function_scopes[function_depth - 1] && strcmp(s->type, "local variable") == 0) allowed = 1;

			else if(s->scope == 0) allowed = 1;

			if(allowed == 0) { 
				printf("ERROR: use of variable \"%s\" from outer function more than one scope away at line %d\n", s->name, t.line);
			}
		}*/

		/* if it is a function */
		else if(s != NULL && strcmp(s->type, "function") == 0){
			current_lvalue = s;
		}

		{ print_reduce("lvalue", "ID"); }
	}
	| LOCAL ID { /* if the symbol doesn't exist or is hidden in current scope and not library function name, then it's added */
		Symbol* s = SymTable_lookup_scope(sym_table, $2, current_scope);
		Symbol* lib = SymTable_lookup_scope(sym_table, $2, 0);

                if(lib != NULL && strcmp(lib->type, "library function") == 0){
			char error_message[200];
                        sprintf(error_message, "ERROR: use of library function \"%s\" as local at line %d", lib->name, t.line);
                	add_new_error(error_message);
		}
				
		else if(s == NULL || s->isActive == 0){
                        if(current_scope == 0) 
				s = Symbol_create($2, "global variable", current_scope, t.line, 1);
			else 
				s = Symbol_create($2, "local variable", current_scope, t.line, 1);
                        
			SymTable_put(sym_table, s);
                }

		print_reduce("lvalue", "LOCAL ID");
        } 
	| DOUBLE_COLON ID { /* lookup in scope 0 */
		Symbol* s = SymTable_lookup_scope(sym_table, $2, 0);

		if(s == NULL){
			char error_message[200];
			sprintf(error_message, "ERROR: undefined global variable %s at line %d", $2, t.line);
			add_new_error(error_message);
		}

		{ print_reduce("lvalue", "DOUBLE_COLON ID"); }
	}
	| member { print_reduce("lvalue", "member"); }
;

member:
	lvalue DOT ID { print_reduce("member", "lvalue DOT ID"); }
	| lvalue LEFT_BRACKET expr RIGHT_BRACKET { print_reduce("member", "lvalue LEFT_BRACKET expr RIGHT_BRACKET"); }
;

call:
    call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { print_reduce("call", "call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
    | lvalue callsuffix { /* check if symbol used as function is in the symbol table and if it is a function */
	if(current_lvalue != NULL){
		Symbol* s = SymTable_lookup(sym_table, current_lvalue->name, current_scope, function_depth, function_scopes);

		if(s == NULL){
			char error_message[200];
        		sprintf(error_message, "ERROR: undefined function %s at line %d", current_lvalue->name, t.line);
			add_new_error(error_message);
		}

		else if(s != NULL && strcmp(s->type, "function") != 0){
			char error_message[200];
			sprintf(error_message, "ERROR: %s %s incorrectly used as function at line %d", s->type, current_lvalue->name, t.line);
			add_new_error(error_message);
		}

		current_lvalue = NULL;
	}

	{ print_reduce("call", "lvalue callsuffix"); }
    }
    | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { 
	print_reduce("call", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS");
    }
;

callsuffix:
	normcall { print_reduce("callsuffix", "normcall"); }
	| methodcall { print_reduce("callsuffix", "methodcall"); }
;

normcall:
	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { print_reduce("normcall", "LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
;

methodcall:
	  DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { print_reduce("methodcall", "DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
;

elist:
	expr { print_reduce("elist", "expr"); }
	| elist COMMA expr { print_reduce("elist", "elist COMMA expr"); }
	| /* empty */ { print_reduce("elist", "empty"); }
;

objectdef:
	 LEFT_BRACKET obj RIGHT_BRACKET { print_reduce("objectdef", "LEFT_BRACKET obj RIGHT_BRACKET"); }
;

obj:
	elist { print_reduce("obj", "elist"); }
	| indexed { print_reduce("obj", "indexed"); }
;

indexed:
	indexedelem { print_reduce("indexed", "indexedelem"); }
	| indexed COMMA indexedelem { print_reduce("indexed", "indexed COMMA indexedelem"); }
;

indexedelem:
	   LEFT_BRACE expr COLON expr RIGHT_BRACE { print_reduce("indexedelem", "LEFT_BRACE expr COLON expr RIGHT_BRACE"); }
;

block:
	LEFT_BRACE {
		current_scope++;
	} 	
	statements 
	RIGHT_BRACE {	
		SymTable_hide_scope(sym_table, current_scope); 
		current_scope--;

		print_reduce("block", "LEFT_BRACE statement RIGHT_BRACE");
	}
;

funcdef:
       FUNCTION ID {
		Symbol* s = SymTable_lookup_scope(sym_table, $2, current_scope);
                Symbol* lib = SymTable_lookup_scope(sym_table, $2, 0);

                if(lib != NULL && strcmp(lib->type, "library function") == 0){
			char error_message[200];
                        sprintf(error_message, "ERROR: use of library function \"%s\" as function at line %d", lib->name, t.line);
                	add_new_error(error_message);
		}

		else if(s != NULL && s->isActive == 1) {
			char error_message[200];
                        sprintf(error_message, "ERROR: redeclaration of \"%s\" at line %d", $2, t.line);
			add_new_error(error_message);
		}

		else if(s == NULL || s->isActive == 0){
			Symbol* s = Symbol_create($2, "function", current_scope, t.line, 1);
			SymTable_put(sym_table, s);
	
                	function_depth++;
			function_scopes[function_depth] = current_scope;
			function_started = 1;
		}

		current_scope++;
	}
	LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS 
	LEFT_BRACE statements RIGHT_BRACE {
		SymTable_hide_scope(sym_table, current_scope);

		if(function_started == 1){
			function_depth--;
			function_started = 0;
		}

		current_scope--;

		print_reduce("funcdef", "FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block");
	}
;

const:
   	CONST_INT { print_reduce("const", "CONST_INT"); }
	| CONST_REAL { print_reduce("const", "CONST_REAL"); }
	| STRING { print_reduce("const", "STRING"); }
	| NIL { print_reduce("const", "NIL"); }
	| TRUE { print_reduce("const", "TRUE"); }
	| FALSE { print_reduce("const", "FALSE"); }
;

idlist:
	ID { 	
		if(SymTable_lookup_scope(sym_table, $1, current_scope) == NULL){
			Symbol* s = Symbol_create($1, "parameter", current_scope, t.line, 1);
           		SymTable_put(sym_table, s); 
		}

		print_reduce("idlist", "ID");
	}
	| idlist COMMA ID {
		if(SymTable_lookup_scope(sym_table, $3, current_scope) == NULL){
			Symbol* s = Symbol_create($3, "parameter", current_scope, t.line, 1);
                	SymTable_put(sym_table, s);
		}

		print_reduce("idlist", "idlist COMMA ID");
        }
	| /* empty */ { print_reduce("idlist", "empty"); }
;

ifstmt:
	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt %prec IFX { print_reduce("ifstmt", "IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt"); }
	| IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt elsestmt { print_reduce("ifstmt", "IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt elsestmt"); }
;

elsestmt:
	ELSE stmt { print_reduce("elsestmt", "ELSE stmt"); }
;

whilestmt:
	 WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
        { loop_depth++; }
        stmt
        { 
		loop_depth--; 
		
		print_reduce("whilestmt", "WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt");
	}
;

forstmt:
	FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS 
	{ loop_depth++; }
	stmt
	{ 
		loop_depth--; 

		print_reduce("forstmt", "FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS");
	}
;

returnstmt:
	RETURN returnvalue SEMI_COLON {
		if(function_depth == -1){
			char error_message[200];
			sprintf(error_message ,"ERROR: return called outside of function at line %d", t.line); 
			add_new_error(error_message);
		}

		print_reduce("returnstmt", "RETURN returnvalue SEMI_COLON");
	}
;

returnvalue:
	expr { print_reduce("returnvalue", "expr"); }
	| /* empty */ { print_reduce("returnvalue", "empty"); }
;

%%

int main(int argc, char **argv) {

	assert(argc == 2);

	yyin = fopen(argv[1], "r");
	assert(yyin);

	printf("Parsing started.\n");

	sym_table = SymTable_create();

	/* library functions */
	SymTable_put(sym_table, Symbol_create("print", "library function", 0, 0, 1));
	SymTable_put(sym_table, Symbol_create("input", "library function", 0, 0, 1));
	SymTable_put(sym_table, Symbol_create("objectmemberkeys", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("objecttotalmembers", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("objectcopy", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("totalarguments", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("argument", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("typeof", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("strtonum", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("sqrt", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("cos", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("sin", "library function", 0, 0, 1));

	if(yyparse() != 0) {
        	SymTable_free(sym_table);
        	return 1;
    	}	

    	printf("Parsing finished.\n");

	print_errors();
	
	SymTable_print(sym_table);

	SymTable_free(sym_table);
	free_errors();
	fclose(yyin);
    	
	return 0;
}

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

