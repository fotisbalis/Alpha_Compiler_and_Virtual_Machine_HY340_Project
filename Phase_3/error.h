typedef struct Error {
	char* message;
	struct Error *next;
} Error;

void add_new_error(char* error_message);

int has_errors();

int error_count();

void print_errors();

void free_errors();
