%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "token.h"
#include "symbol_table.h"
#include "error.h"
#include "symbol.h"
#include "utils.h"
#include "pending_labels.h"
#include "expr.h"
#include "indexed.h"
#include "quad.h"
#include "loop_info.h"
#include "stmt.h"
#include "callsuffix.h"

#define NO_LABEL -1
#define True 1
#define False 0

extern FILE *yyin;
extern int alpha_yylex(Token *token);
Token t;

SymTable_T sym_table;
int current_scope = 0, loop_depth = -1, function_depth = -1, function_scopes[100], function_started = 0, anonymous_function_counter = 0;
Symbol* current_lvalue = NULL; 

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
	Expr* exprNode;
	ExprList* exprList;
	CallSuffix* callSuffix;
	Stmt* stmtNode;
	PendingLabel* pendingLabels;
	int quadID;
	LoopQuads whileQuads;
	LoopQuads forQuads;
	Indexed* indexedNode;
	IndexedList* indexedList;
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

%type <exprNode> expr term primary lvalue const assignexpr member call funcstart funcdef returnvalue objectdef
%type <exprList> elist nonempty_elist
%type <callSuffix> callsuffix normcall methodcall
%type <stmtNode> stmt statements block ifstmt whilestmt forstmt returnstmt
%type <quadID> ifcond elsestart whilestart forstart forstep forstepstart forbodystart jump_func forcheck
%type <whileQuads> whilecond
%type <forQuads> forcond
%type <indexedNode> indexedelem
%type <indexedList> indexed

%%

program:
       statements { print_reduce("program", "statements"); }
;

statements:
	/* empty */ { 
		$$ = create_stmt();
		print_reduce("statements", "empty"); 
	}
	| stmt statements {
		$$ = create_stmt();
		
		$$->BreakLabels = merge_jump_lists($1->BreakLabels, $2->BreakLabels);
        	$$->ContinueLabels = merge_jump_lists($1->ContinueLabels, $2->ContinueLabels);
		$$->ReturnLabels = merge_jump_lists($1->ReturnLabels, $2->ReturnLabels);

		print_reduce("statements", "stmt statement");
	} 
	| LINE_COMMENT statements { 
		$$ = $2;
		print_reduce("statements", "LINE_COMMENT statements"); 
	}
	| BLOCK_COMMENT statements {
                $$ = $2;
                print_reduce("statements", "BLOCK_COMMENT statements"); 
	}
	| NESTED_COMMENT statements {
                $$ = $2;
                print_reduce("statements", "NESTED_COMMENT statements"); 
	}
;

stmt:
	expr SEMI_COLON {
		$$ = create_stmt();
		print_reduce("stmt", "expr SEMI_COLON"); 
	}
	| ifstmt {
                $$ = $1;
                print_reduce("stmt", "ifstmt"); 
	}
	| whilestmt {
                $$ = $1;
                print_reduce("stmt", "whilestmt"); 
	}
	| forstmt {
                $$ = $1;
                print_reduce("stmt", "forstmt"); 
	}
	| returnstmt {
		$$ = $1;
		print_reduce("stmt", "returnstmt"); 
	}
	| BREAK SEMI_COLON {
		$$ = create_stmt();

		if(loop_depth == -1){
			char error_message[200];
			sprintf(error_message, "ERROR: break called outside of loop at line %d", t.line);
			add_new_error(error_message);				
		}
		else {
			int quad = get_quad_count();
			new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
			$$->BreakLabels = create_pending_label(quad);
		}
		
		print_reduce("stmt", "BREAK SEMI_COLON");
	}
	| CONTINUE SEMI_COLON {
		$$ = create_stmt();

                if(loop_depth == -1){
                        char error_message[200];
                        sprintf(error_message, "ERROR: continue called outside of loop at line %d", t.line);
                        add_new_error(error_message);
                }
		else {
                        int quadID = get_quad_count();
                        new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
                        $$->ContinueLabels = create_pending_label(quadID);
                }
		
		print_reduce("stmt", "CONTINUE SEMI_COLON");
	}
	| block {
                $$ = $1;
                print_reduce("stmt", "block"); 
	}
	| funcdef {
                $$ = create_stmt();
                print_reduce("stmt", "funcdef"); 
	}
	| SEMI_COLON {
		$$ = create_stmt();
		print_reduce("stmt", "SEMI_COLON"); 
	}
;

expr:
	assignexpr {
		$$ = $1;
		print_reduce("expr", "assignexpr");
	}
	| expr PLUS expr {
		Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
		$$ = lvalue_expr(tmp, arithexpr);
		new_quad(_add, $$, emit_bool_expr($1, sym_table, current_scope, t.line), emit_bool_expr($3, sym_table, current_scope, t.line), NO_LABEL);

		print_reduce("expr", "expr PLUS expr"); 
	}
	| expr MINUS expr {
		Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
                $$ = lvalue_expr(tmp, arithexpr);
                new_quad(_sub, $$, emit_bool_expr($1, sym_table, current_scope, t.line), emit_bool_expr($3, sym_table, current_scope, t.line), NO_LABEL);

		print_reduce("expr", "expr MINUS expr"); 
	}
        | expr MULTIPLY expr {
                Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
                $$ = lvalue_expr(tmp, arithexpr);
                new_quad(_mul, $$, emit_bool_expr($1, sym_table, current_scope, t.line), emit_bool_expr($3, sym_table, current_scope, t.line), NO_LABEL);

                print_reduce("expr", "expr MULTIPLY expr"); 
	}
        | expr DIVISION expr {
                Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
                $$ = lvalue_expr(tmp, arithexpr);
                new_quad(_div, $$, emit_bool_expr($1, sym_table, current_scope, t.line), emit_bool_expr($3, sym_table, current_scope, t.line), NO_LABEL);

                print_reduce("expr", "expr DIVISION expr");
	}
        | expr MOD expr {
                Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
                $$ = lvalue_expr(tmp, arithexpr);
                new_quad(_mod, $$, emit_bool_expr($1, sym_table, current_scope, t.line), emit_bool_expr($3, sym_table, current_scope, t.line), NO_LABEL);

                print_reduce("expr", "expr MOD expr"); 
	}
        | expr GREATER expr {
		$$ = handle_comparison_quad(if_greater, $1, $3, sym_table, current_scope, t.line);				

		print_reduce("expr", "expr GREATER expr");
	}
        | expr GREATER_EQUAL expr { 
		$$ = handle_comparison_quad(if_greatereq, $1, $3, sym_table, current_scope, t.line);

		print_reduce("expr", "expr GREATER_EQUAL expr"); 
	}
        | expr LESS expr {
                $$ = handle_comparison_quad(if_less, $1, $3, sym_table, current_scope, t.line);

                print_reduce("expr", "expr LESS expr"); 
	}
        | expr LESS_EQUAL expr {
                $$ = handle_comparison_quad(if_lesseq, $1, $3, sym_table, current_scope, t.line);

                print_reduce("expr", "expr LESS_EQUAL expr"); 
	}
        | expr EQUAL expr {
                $$ = handle_comparison_quad(if_eq, $1, $3, sym_table, current_scope, t.line);

                print_reduce("expr", "expr EQUAL expr");
	}
        | expr NOT_EQUAL expr {
                $$ = handle_comparison_quad(if_noteq, $1, $3, sym_table, current_scope, t.line);

                print_reduce("expr", "expr NOT_EQUAL expr"); 
	}
        | expr AND {
		Expr *left = convert_expr_to_bool($1, sym_table, current_scope, t.line);
		fill_pending_labels_of_list(left->PendingTrueJumps, get_quad_count());
		$<exprNode>$ = left;
	} expr {
		Expr *left = $<exprNode>3;
		Expr *right = convert_expr_to_bool($4, sym_table, current_scope, t.line);

		$$ = create_expr(boolexpr);
		$$->PendingTrueJumps = right->PendingTrueJumps;
		$$->PendingFalseJumps = merge_jump_lists(left->PendingFalseJumps, right->PendingFalseJumps);

		print_reduce("expr", "expr AND expr");
	}
        | expr OR {
		Expr *left = convert_expr_to_bool($1, sym_table, current_scope, t.line);
		fill_pending_labels_of_list(left->PendingFalseJumps, get_quad_count());
		$<exprNode>$ = left;
	} expr {
		Expr *left = $<exprNode>3;
		Expr *right = convert_expr_to_bool($4, sym_table, current_scope, t.line);

		$$ = create_expr(boolexpr);
		$$->PendingTrueJumps = merge_jump_lists(left->PendingTrueJumps, right->PendingTrueJumps);
		$$->PendingFalseJumps = right->PendingFalseJumps;

		print_reduce("expr", "expr OR expr"); 
	}
	| term { 
		$$ = $1;
		print_reduce("expr", "term");
	}
;

term:
    	LEFT_PARENTHESIS expr RIGHT_PARENTHESIS { 
		$$ = $2;
		print_reduce("term", "LEFT_PARENTHESIS expr RIGHT_PARENTHESIS"); 
	}
	| MINUS expr %prec UMINUS { 
		Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
                $$ = lvalue_expr(tmp, arithexpr);
                new_quad(_uminus, $$, emit_bool_expr($2, sym_table, current_scope, t.line), NULL, NO_LABEL);

		print_reduce("term", "MINUS expr");
	}
	| NOT expr {
		$$ = convert_expr_to_bool($2, sym_table, current_scope, t.line);
		swap_true_false_lists($$);

		print_reduce("term", "NOT expr");
	}
	| PLUS_PLUS lvalue {
		$$ = handle_pre_inc_dec($2, _add, sym_table, current_scope, t.line);

		print_reduce("term", "PLUS_PLUS lvalue"); 
	}
	| lvalue PLUS_PLUS {
		$$ = handle_post_inc_dec($1, _add, sym_table, current_scope, t.line);

		print_reduce("term", "lvalue PLUS_PLUS");
	}
	| MINUS_MINUS lvalue {
		$$ = handle_pre_inc_dec($2, _sub, sym_table, current_scope, t.line);

		print_reduce("term", "MINUS_MINUS lvalue"); 
	}
	| lvalue MINUS_MINUS {
		$$ = handle_post_inc_dec($1, _sub, sym_table, current_scope, t.line);

		print_reduce("term", "lvalue MINUS_MINUS");
	}
	| primary { 
		$$ = $1;
		print_reduce("term", "primary"); 
	}
;

assignexpr:
	lvalue ASSIGN expr { 
		Symbol *tmp = new_tmp(sym_table, current_scope, t.line);
		Expr *result = lvalue_expr(tmp, assignexpr);
		Expr *value = emit_bool_expr($3, sym_table, current_scope, t.line);

		if(current_lvalue != NULL){
			if(strcmp(current_lvalue->type, "function") == 0) {
                        	char error_message[200];
                        	sprintf(error_message, "ERROR: assign to function \"%s\" at line %d", current_lvalue->name, t.line);
                        	add_new_error(error_message);	
			}
		}

		if($1 == NULL || ($1->type != tableitem && $1->sym == NULL)){
			$$ = error_expr(assignexpr);
		}
		else if($1->type != tableitem){
			new_quad(_assign, $1, value, NULL, NO_LABEL);
			new_quad(_assign, result, $1, NULL, NO_LABEL);
			$$ = result;
		}
		else{
			Expr *table = lvalue_expr($1->sym, var);
			new_quad(tablesetelem, table, $1->table_index, value, NO_LABEL);
			new_quad(tablegetelem, result, table, $1->table_index, NO_LABEL);
			$$ = result;
		}

		print_reduce("assignexpr", "lvalue ASSIGN expr"); 
	}
;

primary:
       	lvalue { 
		$$ = emit_table_item($1, sym_table, current_scope, t.line);
		print_reduce("primary", "lvalue");
	}
	| call {
		$$ = $1; 
		print_reduce("primary", "call"); 
	}
	| objectdef {
		$$ = $1;
                print_reduce("primary", "objectdef"); 
	}
	| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS {
                print_reduce("primary", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS");
	} 
	| const {
		$$ = $1;
		print_reduce("primary", "const");
	}
;

lvalue:
	ID { /* add in current scope */
		current_lvalue = NULL;
		Symbol *s = SymTable_lookup(sym_table, $1, current_scope, function_depth, function_scopes);

		if(s == NULL){
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
						s = Symbol_create($1, "local variable", current_scope, t.line, 1, 0);
						SymTable_put(sym_table, s);
					}
				}
				else {
					s = Symbol_create($1, "local variable", current_scope, t.line, 1, 0);
					SymTable_put(sym_table, s);
				}
			}
			else if(current_scope == 0){
                                s = Symbol_create($1, "global variable", current_scope, t.line, 1, 0);
				SymTable_put(sym_table, s);
			}
                        else {
                                s = Symbol_create($1, "variable", current_scope, t.line, 1, 0);		
				SymTable_put(sym_table, s);
			}
		}

		/* if it is a function */
		else if(s != NULL && strcmp(s->type, "function") == 0){
			current_lvalue = s;
		}

		$$ = lvalue_expr(s, var);
		print_reduce("lvalue", "ID");
	}
	| LOCAL ID { /* if the symbol doesn't exist or is hidden in current scope and not library function name, then it's added */
		Symbol* s = SymTable_lookup_scope(sym_table, $2, current_scope);
		
		Symbol* lib = check_for_lib_func(sym_table, $2);

                if(lib != NULL){
			char error_message[200];
                        sprintf(error_message, "ERROR: use of library function \"%s\" as local at line %d", lib->name, t.line);
                	add_new_error(error_message);
			$$ = error_expr(var);
		}
				
		else if(s == NULL || s->isActive == 0){
                        if(current_scope == 0) 
				s = Symbol_create($2, "global variable", current_scope, t.line, 1, 0);
			else 
				s = Symbol_create($2, "local variable", current_scope, t.line, 1, 0);
                         
			SymTable_put(sym_table, s);
			$$ = lvalue_expr(s, var);
                 }

		else
			$$ = lvalue_expr(s, var);
	
		print_reduce("lvalue", "LOCAL ID");
        } 
	| DOUBLE_COLON ID { /* lookup in scope 0 */
		Symbol* s = SymTable_lookup_scope(sym_table, $2, 0);

		if(s == NULL){
			char error_message[200];
			sprintf(error_message, "ERROR: undefined global variable %s at line %d", $2, t.line);
			add_new_error(error_message);
			$$ = error_expr(var);
		}
		else
			$$ = lvalue_expr(s, var);

		print_reduce("lvalue", "DOUBLE_COLON ID");
	}
	| member { 
		$$ = $1;

		print_reduce("lvalue", "member"); 
	}
;

member:
	lvalue DOT ID {
		Expr *expr = emit_table_item($1, sym_table, current_scope, t.line);
		$$ = create_member(expr, $3, NULL);		

		print_reduce("member", "lvalue DOT ID"); 
	}
	| lvalue LEFT_BRACKET expr RIGHT_BRACKET {
		Expr *expr = emit_table_item($1, sym_table, current_scope, t.line);

		$$ = create_expr(tableitem);
		$$ = create_member(expr, NULL, $3);

		print_reduce("member", "lvalue LEFT_BRACKET expr RIGHT_BRACKET");
	}
	| call DOT ID {
		Expr *expr = emit_table_item($1, sym_table, current_scope, t.line);
		$$ = create_member(expr, $3, NULL);

		print_reduce("member", "call DOT ID");
	}
        | call LEFT_BRACKET expr RIGHT_BRACKET { 
		Expr *expr = emit_table_item($1, sym_table, current_scope, t.line);

                $$ = create_expr(tableitem);
                $$ = create_member(expr, NULL, $3);

		print_reduce("member", "call LEFT_BRACKET expr RIGHT_BRACKET"); 
	}
;

call:
    call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
	$$ = make_call($1, $3, sym_table, current_scope, t.line);	

	print_reduce("call", "call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); 
    }
    | lvalue callsuffix { /* check if symbol used as function is in the symbol table and if it is a function */
	Expr *func = $1;
	ExprList *params = $2->params;

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

	if($2->is_method){
		Expr *self = emit_table_item($1, sym_table, current_scope, t.line);
		ExprList *method_params = create_expr_list();

		add_expr(method_params, self);

		if(params != NULL && params->head != NULL){
			method_params->tail->next = params->head;
			method_params->tail = params->tail;
		}

		func = create_member(self, $2->method_name, NULL);
		params = method_params;
	}

	$$ = make_call(func, params, sym_table, current_scope, t.line);

	print_reduce("call", "lvalue callsuffix");
    }
    | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
	$$ = make_call($2, $5, sym_table, current_scope, t.line);

	print_reduce("call", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS");
    }
;

callsuffix:
	normcall { 
		$$ = $1;		

		print_reduce("callsuffix", "normcall"); 
	}
	| methodcall {
		$$ = $1;

		print_reduce("callsuffix", "methodcall"); 
	}
;

normcall:
	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { 
		$$ = malloc(sizeof(CallSuffix));
		$$->params = $2;
		$$->is_method = 0;
		$$->method_name = NULL;

		print_reduce("normcall", "LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); 
	}
;

methodcall:
	  DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
		$$ = malloc(sizeof(CallSuffix));
		$$->params = $4;
		$$->is_method = 1;
		$$->method_name = strdup($2);

		print_reduce("methodcall", "DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS");
	  }
;

elist:
     	nonempty_elist {
                $$ = $1;
                print_reduce("elist", "nonempty_elist");
    	}
	| /* empty */ { 
		$$ = create_expr_list();
		print_reduce("elist", "empty"); 
	}
;

nonempty_elist:
	expr {
                $$ = create_expr_list();
                add_expr($$, $1);

                print_reduce("elist", "expr");
        }
        | nonempty_elist COMMA expr {
                $$ = $1;
                add_expr($$, $3);

                print_reduce("elist", "elist COMMA expr");
        }
;

objectdef:
	LEFT_BRACKET RIGHT_BRACKET {
		$$ = create_table(sym_table, current_scope, t.line);
                print_reduce("objectdef", "LEFT_BRACKET RIGHT_BRACKET");
	}
	| LEFT_BRACKET indexed RIGHT_BRACKET {
                $$ = create_table(sym_table, current_scope, t.line);
                add_indexed_to_table($2, $$, sym_table, current_scope, t.line);

                print_reduce("objectdef", "LEFT_BRACKET indexed RIGHT_BRACKET");
        }
	| LEFT_BRACKET nonempty_elist RIGHT_BRACKET { 
		$$ = create_table(sym_table, current_scope, t.line);
		add_elist_to_table($2, $$, sym_table, current_scope, t.line);			

		print_reduce("objectdef", "LEFT_BRACKET elist RIGHT_BRACKET"); 
	}
;

indexed:
	indexedelem { 
		$$ = create_indexed_list();
		add_indexed($$, $1);	

		print_reduce("indexed", "indexedelem"); 
	}
	| indexed COMMA indexedelem { 
		$$ = $1;
                add_indexed($$, $3);		

		print_reduce("indexed", "indexed COMMA indexedelem"); 
	}
;

indexedelem:
	LEFT_BRACE expr COLON expr RIGHT_BRACE { 
		$$ = create_indexed(emit_bool_expr($2, sym_table, current_scope, t.line), emit_bool_expr($4, sym_table, current_scope, t.line));		

		print_reduce("indexedelem", "LEFT_BRACE expr COLON expr RIGHT_BRACE"); 
	}
;

block:
	LEFT_BRACE {
		current_scope++;
	} 	
	statements 
	RIGHT_BRACE {
                $$ = $3;
			
		SymTable_hide_scope(sym_table, current_scope); 
		current_scope--;

		print_reduce("block", "LEFT_BRACE statement RIGHT_BRACE");
	}
;

funcstart:
	 FUNCTION ID {
                Symbol* s = SymTable_lookup_scope(sym_table, $2, current_scope);

                Symbol* lib = check_for_lib_func(sym_table, $2);

                if(lib != NULL){
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
                        Symbol* s = Symbol_create($2, "function", current_scope, t.line, 1, 0);
                        SymTable_put(sym_table, s);

			$$ = lvalue_expr(s, programfunc);
			new_quad(funcstart, $$, NULL, NULL, NO_LABEL);

                        function_depth++;
                        function_scopes[function_depth] = current_scope;
                        function_started = 1;
                }

                current_scope++;
		enter_scope_space();
		reset_formal_arg_offset();

		print_reduce("funcstart", "FUNCTION ID");
        }
	| FUNCTION {
                char anonymous_name[32];
                sprintf(anonymous_name, "anon_%d", anonymous_function_counter++);

                Symbol* s = SymTable_lookup_scope(sym_table, anonymous_name, current_scope);

                if(s == NULL || s->isActive == 0){
                        Symbol* s = Symbol_create(anonymous_name, "function", current_scope, t.line, 1, 0);
                        SymTable_put(sym_table, s);

			$$ = lvalue_expr(s, programfunc);
                        new_quad(funcstart, $$, NULL, NULL, NO_LABEL);

                        function_depth++;
                        function_scopes[function_depth] = current_scope;
                        function_started = 1;
                }

                current_scope++;
		enter_scope_space();
		reset_formal_arg_offset();

		print_reduce("funcstart", "FUNCTION");
        }
;

jump_func:
	 {
		$$ = get_quad_count();
	}
;

funcdef:
	jump_func {
		new_quad(_jump, NULL, NULL, NULL, NO_LABEL); /* jump to end of function */
	}
	funcstart LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS 
	{
		exit_scope_space();
		enter_scope_space();
		reset_function_local_offset();
	}
	LEFT_BRACE statements RIGHT_BRACE {
		SymTable_hide_scope(sym_table, current_scope);

		if(function_started == 1){
			fill_pending_labels_of_list($9->ReturnLabels, get_quad_count());
			new_quad(funcend, $3, NULL, NULL, NO_LABEL);
			$$ = $3;			

			fill_pending_label($1, get_quad_count());		

			function_depth--;
			function_started = 0;
		}

		exit_scope_space();
		current_scope--;

		print_reduce("funcdef", "funcstart LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block");
	}
;

const:
   	CONST_INT {
		$$ = num_const_expr($1); 
		print_reduce("const", "CONST_INT");
	}
	| CONST_REAL {
		$$ = num_const_expr($1);
		print_reduce("const", "CONST_REAL"); 
	}
	| STRING { 
		$$ = str_const_expr($1);
		print_reduce("const", "STRING"); 
	}
	| NIL { 
		$$ = nil_expr();
		print_reduce("const", "NIL"); 
	}
	| TRUE {
		$$ = bool_const_expr(1); 
		print_reduce("const", "TRUE"); 
	}
	| FALSE {
		$$ = bool_const_expr(0);
		print_reduce("const", "FALSE");
	}
;

idlist:
	ID { 	
		Symbol* s = SymTable_lookup_scope(sym_table, $1, current_scope);
          
		Symbol* lib = check_for_lib_func(sym_table, $1);

                if(lib != NULL){
                        char error_message[200];
                        sprintf(error_message, "ERROR: formal argument \"%s\" shadows library function at line %d", $1, t.line);
                        add_new_error(error_message);
                }
		else if(s != NULL && s->isActive == 1){
                        char error_message[200];
                        sprintf(error_message, "ERROR: duplicate formal argument \"%s\" at line %d", $1, t.line);
                        add_new_error(error_message);
                }
		else {
			Symbol* s = Symbol_create($1, "parameter", current_scope, t.line, 1, 0);
           		SymTable_put(sym_table, s); 
		}

		print_reduce("idlist", "ID");
	}
	| idlist COMMA ID {
		Symbol* s = SymTable_lookup_scope(sym_table, $3, current_scope);
                
		Symbol* lib = check_for_lib_func(sym_table, $3);

                if(lib != NULL){
                        char error_message[200];
                        sprintf(error_message, "ERROR: formal argument \"%s\" shadows library function at line %d", $3, t.line);
                        add_new_error(error_message);
                }
                else if(s != NULL && s->isActive == 1){
                        char error_message[200];
                        sprintf(error_message, "ERROR: duplicate formal argument \"%s\" at line %d", $3, t.line);
                        add_new_error(error_message);
                }
		else {
			Symbol* s = Symbol_create($3, "parameter", current_scope, t.line, 1, 0);
                	SymTable_put(sym_table, s);
		}

		print_reduce("idlist", "idlist COMMA ID");
        }
	| /* empty */ { print_reduce("idlist", "empty"); }
;

ifcond:
        IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
		Expr *cond = emit_bool_expr($3, sym_table, current_scope, t.line);
		$$ = get_quad_count();

		new_quad(if_eq, NULL, cond, bool_const_expr(True), NO_LABEL);
		new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
	}
;

ifstmt:
	ifcond stmt %prec IFX {
		int if_quadID = $1;		
		int if_quad_label = if_quadID + 2;
		int false_jump_quadID = if_quadID + 1;
		int false_jump_quad_label = get_quad_count();		

		fill_pending_label(if_quadID, if_quad_label);
		fill_pending_label(false_jump_quadID, false_jump_quad_label);

		$$ = $2;

		print_reduce("ifstmt", "IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt"); 
	}
	| ifcond stmt elsestart stmt { 
		int if_quadID = $1;
                int if_quad_label = if_quadID + 2;
                int false_jump_quadID = if_quadID + 1;
		
		int else_jump_quadID = $3;
        	int else_stmt_label = else_jump_quadID + 1;
        	int after_else_label = get_quad_count();

		fill_pending_label(if_quadID, if_quad_label);
		fill_pending_label(false_jump_quadID, else_stmt_label);
		fill_pending_label(else_jump_quadID, after_else_label);

		$$ = create_stmt();
		$$->BreakLabels = merge_jump_lists($2->BreakLabels, $4->BreakLabels);
		$$->ContinueLabels = merge_jump_lists($2->ContinueLabels, $4->ContinueLabels);
		$$->ReturnLabels = merge_jump_lists($2->ReturnLabels, $4->ReturnLabels);

		print_reduce("ifstmt", "IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt"); 
	}
;

elsestart:
	ELSE {
		$$ = get_quad_count();

        	new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
	}
;

whilestart:
	WHILE {
		$$ = get_quad_count();
	}
;

whilecond:
	whilestart LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {
		Expr *cond = emit_bool_expr($3, sym_table, current_scope, t.line);
		$$.cond_quadID = $1;
		$$.if_true_quadID = get_quad_count();

		new_quad(if_eq, NULL, cond, bool_const_expr(True), NO_LABEL);
                new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
	}
;

whilestmt:
	whilecond
        { loop_depth++; }
	stmt
        {
		int if_quadID = $1.if_true_quadID;
		int false_jump_quadID = if_quadID + 1;
		int body_label = if_quadID + 2;
		
		fill_pending_label(if_quadID, body_label);
        	
		fill_pending_labels_of_list($3->ContinueLabels, $1.cond_quadID);	
		
		fill_pending_label(false_jump_quadID, get_quad_count() + 1);

		fill_pending_labels_of_list($3->BreakLabels, get_quad_count() + 1);

		new_quad(_jump, NULL, NULL, NULL, $1.cond_quadID);

		$$ = create_stmt();
		$$->ReturnLabels = $3->ReturnLabels;

		loop_depth--;

		print_reduce("whilestmt", "WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt");
	}
;

forstart:
	FOR {
                $$ = get_quad_count();
        }
;

forcheck:
	{
		$$ = get_quad_count();
	}
;

forcond:
	forstart LEFT_PARENTHESIS elist SEMI_COLON forcheck expr SEMI_COLON {
		Expr *cond = emit_bool_expr($6, sym_table, current_scope, t.line);
		$$.cond_quadID = $5;
		$$.if_true_quadID = get_quad_count();

		new_quad(if_eq, NULL, cond, bool_const_expr(True), NO_LABEL);
                new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
	}
;

forstep:
	forstepstart elist RIGHT_PARENTHESIS {
		$$ = $1;
	}
;

forstepstart:
	{
                $$ = get_quad_count();
        }
;

forbodystart:
	{
		$$ = get_quad_count();
	}
;

forstmt:
	forcond forstep
	{ 
		new_quad(_jump, NULL, NULL, NULL, $1.cond_quadID);
		loop_depth++; 
	}
	forbodystart stmt
	{
		int if_quadID = $1.if_true_quadID;
                int false_jump_quadID = if_quadID + 1;
                int body_start = $4;
		int step_start = $2;

                fill_pending_label(if_quadID, body_start);

                fill_pending_labels_of_list($5->ContinueLabels, step_start);

                fill_pending_label(false_jump_quadID, get_quad_count() + 1);

                fill_pending_labels_of_list($5->BreakLabels, get_quad_count() + 1);

                new_quad(_jump, NULL, NULL, NULL, step_start);

                $$ = create_stmt();
		$$->ReturnLabels = $5->ReturnLabels;

		loop_depth--; 

		print_reduce("forstmt", "FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS");
	}
;

returnstmt:
	RETURN returnvalue SEMI_COLON {
		$$ = create_stmt();

		if(function_depth == -1){
			char error_message[200];
			sprintf(error_message ,"ERROR: return called outside of function at line %d", t.line); 
			add_new_error(error_message);
		}
		else {
			int return_jump_quadID;

			new_quad(_return, emit_bool_expr($2, sym_table, current_scope, t.line), NULL, NULL, NO_LABEL);
			return_jump_quadID = get_quad_count();
			new_quad(_jump, NULL, NULL, NULL, NO_LABEL);
			$$->ReturnLabels = create_pending_label(return_jump_quadID);
		}

		print_reduce("returnstmt", "RETURN returnvalue SEMI_COLON");
	}
;

returnvalue:
	expr { 
		$$ = $1;
		print_reduce("returnvalue", "expr"); 
	}
	| /* empty */ { 
		$$ = NULL;
		print_reduce("returnvalue", "empty"); 
	}
;

%%

int main(int argc, char **argv) {

	assert(argc == 2);

	yyin = fopen(argv[1], "r");
	assert(yyin);

	printf("Parsing started.\n");

	sym_table = SymTable_create();

	/* library functions */
	SymTable_put(sym_table, Symbol_create("print", "library function", 0, 0, 1, 0));
	SymTable_put(sym_table, Symbol_create("input", "library function", 0, 0, 1, 0));
	SymTable_put(sym_table, Symbol_create("objectmemberkeys", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("objecttotalmembers", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("objectcopy", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("totalarguments", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("argument", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("typeof", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("strtonum", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("sqrt", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("cos", "library function", 0, 0, 1, 0));
        SymTable_put(sym_table, Symbol_create("sin", "library function", 0, 0, 1, 0));

	if(yyparse() != 0) {
        	SymTable_free(sym_table);
		free_errors();
		free_quads();
        	return 1;
    	}	

    	printf("Parsing finished.\n");
	
	print_errors();
	
	SymTable_print(sym_table);

	FILE *quad_file = fopen("quads.txt", "w");
        assert(quad_file);

	print_quads(quad_file);

	SymTable_free(sym_table);
	free_errors();
	free_quads();

	fclose(quad_file);
	fclose(yyin);

	return 0;
}

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}
