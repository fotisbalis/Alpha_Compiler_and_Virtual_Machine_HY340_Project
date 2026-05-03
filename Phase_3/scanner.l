%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "pending_labels.h"
#include "expr.h"
#include "while.h"
#include "parser.tab.h"

#define YY_DECL int alpha_yylex(Token *token)

int counter = 0; /* token counter */
char str[1000]; /* temporary string storage */
int nested_comments; /* counter of nested comments inside a comment */
int start_line[1000]; /* line where every nested comment starts, can work for up to 1000 nested comments */

/* function that assigns every token's characteristics */
void assign_token(Token* t, char *type, char *content, char *name){
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(content);
	t->type = (char*) type;
	t->name = (char*) name;
}

%}

%option noyywrap
%option yylineno
%x STRING
%x COMMENT

%%

"//".* { /* SINGLE LINE COMMENT */ 
	assign_token(token, "COMMENT", "", "LINE_COMMENT");
        return LINE_COMMENT;
}

"/*" { /* BLOCK COMMENTS */
	BEGIN(COMMENT);
	nested_comments = 0;
	start_line[0] = yylineno; /* start_line of first comment */
}

<COMMENT>"/*" { /* nested comment inside comment */
	nested_comments++;
	start_line[nested_comments] = yylineno;
}

<COMMENT>"*/" {	/* Comment closes */
	/* nested comment closes */
	if(nested_comments > 0){
		Token* t = (Token*) token;
                t->line = start_line[nested_comments];
                t->count = ++counter;
                t->type = "COMMENT";
                t->name = "NESTED_COMMENT";

                /* make content "(start_line) - (end_line)" */
                char content[100];
                sprintf(content, "%d - %d", t->line, yylineno);
                t->content = strdup(content);

		nested_comments--;

		return NESTED_COMMENT;
	}

	/* The block closes */
	else if(nested_comments == 0){	
		Token* t = (Token*) token;
       		t->line = start_line[nested_comments];
      	 	t->count = ++counter;
       		t->type = "COMMENT";
		t->name = "BLOCK_COMMENT";
		
		/* make content "(start_line) - (end_line)" */
		char content[100];
		sprintf(content, "%d - %d", t->line, yylineno);
		t->content = strdup(content);

		BEGIN(INITIAL);
		return BLOCK_COMMENT;
	}
}

<COMMENT>\n { /* ignore line changes */ }
<COMMENT>. { /* ignore everything else */ }

<COMMENT><<EOF>> {
        /* End of comment with EOF, return ERROR */
        printf("Error: Comment ends with EOF at line %d\n", yylineno);
        BEGIN(INITIAL);

        return 0;
}

\" {	/* STRINGS */
	BEGIN(STRING);

	/* Initialize the string */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->type = "STRING";

	str[0]='\0';
}

<STRING>\\n { strcat(str, "\n"); /* if '\\n' */}
<STRING>\\t { strcat(str, "\t"); /* if '\\t' */}
<STRING>\\\\ { strcat(str, "\\"); /* if '\\' */}
<STRING>\\\" { strcat(str, "\""); /* if '\"' */}
<STRING>[^\\"]+ { strcat(str, yytext); /* everything else except '"' */ }

<STRING>\" {
	/* Normal end of string */	
	Token* t = (Token*) token;
	t->content = strdup(str);
	t->name = strdup(str);

	yylval.strVal = strdup(str);

	BEGIN(INITIAL);

        return STRING;
}

<STRING><<EOF>> {
	/* End of string with EOF, return ERROR */
	printf("Error: String ends with EOF at line %d\n", yylineno);
	BEGIN(INITIAL);

 	return 0;
}

"{" {	/* PUNCTUATIONS */
        assign_token(token, "PUNCTUATION", yytext, "LEFT_BRACE");
        return LEFT_BRACE;
}

"}" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_BRACE");
        return RIGHT_BRACE;
}

"[" {
        assign_token(token, "PUNCTUATION", yytext, "LEFT_BRACKET");
        return LEFT_BRACKET;
}

"]" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_BRACKET");
        return RIGHT_BRACKET;
}

"(" {
        assign_token(token, "PUNCTUATION", yytext, "LEFT_PARENTHESIS");
        return LEFT_PARENTHESIS;
}

")" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_PARENTHESIS");
        return RIGHT_PARENTHESIS;
}

"::" {
        assign_token(token, "PUNCTUATION", yytext, "DOUBLE_COLON");
        return DOUBLE_COLON;
}

".." {
        assign_token(token, "PUNCTUATION", yytext, "DOUBLE_DOT");
        return DOUBLE_DOT;
}

":" {
        assign_token(token, "PUNCTUATION", yytext, "COLON");
        return COLON;
}

"." {
        assign_token(token, "PUNCTUATION", yytext, "DOT");
        return DOT;
}

"," {
        assign_token(token, "PUNCTUATION", yytext, "COMMA");
        return COMMA;
}

";" {
        assign_token(token, "PUNCTUATION", yytext, "SEMI_COLON");
        return SEMI_COLON;
}

"if" {	/* KEYWORDS */
	assign_token(token, "KEYWORD", yytext, "IF");
	return IF;
}

"else" {
	assign_token(token, "KEYWORD", yytext, "ELSE");
	return ELSE;
}

"while" {
	assign_token(token, "KEYWORD", yytext, "WHILE");
	return WHILE;
}

"for" {
	assign_token(token, "KEYWORD", yytext, "FOR");
	return FOR;
}

"function" {
	assign_token(token, "KEYWORD", yytext, "FUNCTION");
	return FUNCTION;
}

"break" {
	assign_token(token, "KEYWORD", yytext, "BREAK");
	return BREAK;
}

"continue" {
	assign_token(token, "KEYWORD", yytext, "CONTINUE");
	return CONTINUE;
}

"return" {
	assign_token(token, "KEYWORD", yytext, "RETURN");
	return RETURN;
}

"and" {
	assign_token(token, "KEYWORD", yytext, "AND");
	return AND;
}

"not" {
        assign_token(token, "KEYWORD", yytext, "NOT");
        return NOT;
}

"or" {
        assign_token(token, "KEYWORD", yytext, "OR");
        return OR;
}

"local" {
        assign_token(token, "KEYWORD", yytext, "LOCAL");
        return LOCAL;
}

"true" {
        assign_token(token, "KEYWORD", yytext, "TRUE");
        return TRUE;
}

"false" {
        assign_token(token, "KEYWORD", yytext, "FALSE");
        return FALSE;
}

"nil" {
        assign_token(token, "KEYWORD", yytext, "NIL");
        return NIL;
}

"==" {	/* OPERATORS */
	assign_token(token, "OPERATOR", yytext, "EQUAL");
	return EQUAL;
}

"!=" {
	assign_token(token, "OPERATOR", yytext, "NOT_EQUAL");
 	return NOT_EQUAL;
}

"<=" {
	assign_token(token, "OPERATOR", yytext, "LESS_EQUAL");
	return LESS_EQUAL;
}

">=" {
	assign_token(token, "OPERATOR", yytext, "GREATER_EQUAL");
	return GREATER_EQUAL;
}

"=" {
	assign_token(token, "OPERATOR", yytext, "ASSIGN");
	return ASSIGN;
}

"<" {
	assign_token(token, "OPERATOR", yytext, "LESS");
	return LESS;
}

">" {
	assign_token(token, "OPERATOR", yytext, "GREATER");
	return GREATER;
}

"++" {
	assign_token(token, "OPERATOR", yytext, "PLUS_PLUS");
	return PLUS_PLUS;
}

"+" {
	assign_token(token, "OPERATOR", yytext, "PLUS");
	return PLUS;
}

"--" {
	assign_token(token, "OPERATOR", yytext, "MINUS_MINUS");
	return MINUS_MINUS;
}

"-" {
	assign_token(token, "OPERATOR", yytext, "MINUS");
	return MINUS;
}

"*" {
	assign_token(token, "OPERATOR", yytext, "MULTIPLY");
 	return MULTIPLY;
}

"/" {
	assign_token(token, "OPERATOR", yytext, "DIVISION");
	return DIVISION;
}

"%" {
	assign_token(token, "OPERATOR", yytext, "MOD");
	return MOD;
}


[0-9]+"."[0-9]+ {	/* REAL CONSTANT */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "CONST_REAL";
        t->name = strdup(yytext);

	yylval.realVal = strtod(yytext, NULL);
	return CONST_REAL;
}

[0-9]+ {	/* INT CONSTANT */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "CONST_INT";
	t->name = strdup(yytext);

	yylval.intVal = atoi(yytext);
	return CONST_INT;
}

[a-zA-Z_][a-zA-Z0-9_]* {  /* ID */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "ID";
	t->name = strdup(yytext);

	yylval.idVal = strdup(yytext);
	return ID;
}

[ \t\n]+ { /* IGNORE WHITESPACE, TAB, NEWLINE */}

. {	/* UNDEFINED INPUT */
	printf("Undefined input \"%s\" at line %d\n", yytext, yylineno);
}

%%

