%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
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
        return 1;
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

		return 1;
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
		return 1;
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
	BEGIN(INITIAL);

        return 1;
}

<STRING><<EOF>> {
	/* End of string with EOF, return ERROR */
	printf("Error: String ends with EOF at line %d\n", yylineno);
	BEGIN(INITIAL);

 	return 0;
}

"{" {	/* PUNCTUATIONS */
        assign_token(token, "PUNCTUATION", yytext, "LEFT_BRACE");
        return 1;
}

"}" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_BRACE");
        return 1;
}

"[" {
        assign_token(token, "PUNCTUATION", yytext, "LEFT_BRACKET");
        return 1;
}

"]" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_BRACKET");
        return 1;
}

"(" {
        assign_token(token, "PUNCTUATION", yytext, "LEFT_PARENTHESIS");
        return 1;
}

")" {
        assign_token(token, "PUNCTUATION", yytext, "RIGHT_PARENTHESIS");
        return 1;
}

"::" {
        assign_token(token, "PUNCTUATION", yytext, "DOUBLE_COLON");
        return 1;
}

".." {
        assign_token(token, "PUNCTUATION", yytext, "DOUBLE_DOT");
        return 1;
}

":" {
        assign_token(token, "PUNCTUATION", yytext, "COLON");
        return 1;
}

"." {
        assign_token(token, "PUNCTUATION", yytext, "DOT");
        return 1;
}

"," {
        assign_token(token, "PUNCTUATION", yytext, "COMMA");
        return 1;
}

";" {
        assign_token(token, "PUNCTUATION", yytext, "SEMI_COLON");
        return 1;
}

"if" {	/* KEYWORDS */
	assign_token(token, "KEYWORD", yytext, "IF");
	return 1;
}

"else" {
	assign_token(token, "KEYWORD", yytext, "ELSE");
	return 1;
}

"while" {
	assign_token(token, "KEYWORD", yytext, "WHILE");
	return 1;
}

"for" {
	assign_token(token, "KEYWORD", yytext, "FOR");
	return 1;
}

"function" {
	assign_token(token, "KEYWORD", yytext, "FUNCTION");
	return 1;
}

"break" {
	assign_token(token, "KEYWORD", yytext, "BREAK");
	return 1;
}

"continue" {
	assign_token(token, "KEYWORD", yytext, "CONTINUE");
	return 1;
}

"return" {
	assign_token(token, "KEYWORD", yytext, "RETURN");
	return 1;
}

"and" {
	assign_token(token, "KEYWORD", yytext, "AND");
	return 1;
}

"not" {
        assign_token(token, "KEYWORD", yytext, "NOT");
        return 1;
}

"or" {
        assign_token(token, "KEYWORD", yytext, "OR");
        return 1;
}

"local" {
        assign_token(token, "KEYWORD", yytext, "LOCAL");
        return 1;
}

"true" {
        assign_token(token, "KEYWORD", yytext, "TRUE");
        return 1;
}

"false" {
        assign_token(token, "KEYWORD", yytext, "FALSE");
        return 1;
}

"nil" {
        assign_token(token, "KEYWORD", yytext, "NIL");
        return 1;
}

"==" {	/* OPERATORS */
	assign_token(token, "OPERATOR", yytext, "EQUAL");
	return 1;
}

"!=" {
	assign_token(token, "OPERATOR", yytext, "NOT_EQUAL");
 	return 1;
}

"<=" {
	assign_token(token, "OPERATOR", yytext, "LESS_EQUAL");
	return 1;
}

">=" {
	assign_token(token, "OPERATOR", yytext, "GREATER_EQUAL");
	return 1;
}

"=" {
	assign_token(token, "OPERATOR", yytext, "ASSIGN");
	return 1;
}

"<" {
	assign_token(token, "OPERATOR", yytext, "LESS");
	return 1;
}

">" {
	assign_token(token, "OPERATOR", yytext, "GREATER");
	return 1;
}

"++" {
	assign_token(token, "OPERATOR", yytext, "PLUS_PLUS");
	return 1;
}

"+" {
	assign_token(token, "OPERATOR", yytext, "PLUS");
	return 1;
}

"--" {
	assign_token(token, "OPERATOR", yytext, "MINUS_MINUS");
	return 1;
}

"-" {
	assign_token(token, "OPERATOR", yytext, "MINUS");
	return 1;
}

"*" {
	assign_token(token, "OPERATOR", yytext, "MULTIPLY");
 	return 1;
}

"/" {
	assign_token(token, "OPERATOR", yytext, "DIVISION");
	return 1;
}

"%" {
	assign_token(token, "OPERATOR", yytext, "MOD");
	return 1;
}


[0-9]+"."[0-9]+ {	/* REAL CONSTANT */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "CONST_REAL";
        t->name = strdup(yytext);
	return 1;
}

[0-9]+ {	/* INT CONSTANT */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "CONST_INT";
	t->name = strdup(yytext);
	return 1;
}

[a-zA-Z_][a-zA-Z0-9_]* {  /* ID */
	Token* t = (Token*) token;
	t->line = yylineno;
	t->count = ++counter;
	t->content = strdup(yytext);
	t->type = "ID";
	t->name = strdup(yytext);
	return 1;
}

[ \t\n]+ { /* IGNORE WHITESPACE, TAB, NEWLINE */}

. {	/* UNDEFINED INPUT */
	printf("Undefined input \"%s\" at line %d\n", yytext, yylineno);
}

%%

