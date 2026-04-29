#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
        int line;
        int count;
        char *content;
        char *type;
        char *name;
	struct Token* next;
} Token;

#endif
