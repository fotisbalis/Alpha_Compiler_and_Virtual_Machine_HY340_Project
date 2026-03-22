typedef struct Token {
        int line;
        int count;
        char *content;
        char *type;
        char *name;
	struct Token* next;
} Token;
