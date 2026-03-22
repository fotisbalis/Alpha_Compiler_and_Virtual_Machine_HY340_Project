#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <string.h>

extern int alpha_yylex(void*);
extern FILE* yyin;

int main(int argc, char** argv) {

	if(argc < 2) {
		printf("No input file given.\n");
		return 1;
	}

	yyin = fopen(argv[1], "r");
	if(!yyin) {
		printf("Cannot open input file\n");
		return 1;
	}

	Token token;
	Token* head = NULL;
	Token* tail = NULL;
	
	/* Adding the tokens in the single linked list of tokens */
	while(alpha_yylex(&token)) {
		Token* new_token = (Token*)malloc(sizeof(Token));
		
		*new_token = token;
		new_token->next = NULL;

		if(head == NULL){
			head = new_token;
			tail = new_token;
		}
		else {
			tail->next = new_token;
			tail = new_token;
		}
	}

	/* Printing the tokens from the list */
	Token* t;
	for(t = head; t != NULL; t = t->next) {
		
		if(strcmp(t->type, "KEYWORD") == 0 || strcmp(t->type, "OPERATOR") == 0 || strcmp(t->type, "PUNCTUATION") == 0 || strcmp(t->type, "COMMENT") == 0)
		       	printf("%d: #%d \"%s\" %s %s <-enumerated\n", t->line, t->count, t->content, t->type, t->name);
		
		else if(strcmp(t->type, "CONST_INT") == 0)
			printf("%d: #%d \"%s\" %s %s <-integer\n", t->line, t->count, t->content, t->type, t->name);
		
		else if(strcmp(t->type, "CONST_REAL") == 0)
			printf("%d: #%d \"%s\" %s %s <-real\n", t->line, t->count, t->content, t->type, t->name);
		
		else if(strcmp(t->type, "ID") == 0 || strcmp(t->type, "STRING") == 0)
			printf("%d: #%d \"%s\" %s \"%s\" <-char*\n", t->line, t->count, t->content, t->type, t->name);
	}

	return 0;
}
