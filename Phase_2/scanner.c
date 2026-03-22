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

	while(alpha_yylex(&token)) {
        printf("Token #%d: type=%s, name=%s, content=\"%s\" at line %d\n",
               token.count, token.type, token.name, token.content, token.line);
    	}

    	fclose(yyin);


	return 0;
}
