Balis Fotios Marios csd4958

Project - Phase 2

Machine tested on: funduki.

The programme implements a syntax analyzer, checking the alpha language grammar in bison. It parses the input, putting all the grmmatical symbols in a symbol table and uses scopes to manage them.
The output shows all the grammar reductions of the parsing and then prints th entire symbol table per scope.

The files used are:
scanner.l (same as Phase 1)
token.h (same as Phase 1)
symbol_table.h (definition of Symbol and SymTable structs and function protoypes for the symbol table)
symbol_table.c (implementation of all the functions from symbol_table.h) 
parser.y (bison grammar rules and main)

Makefile:
make all: Compiles the flex file, then the bison file and then all the .c files together to create the "parser" executable. Then run as ./parser [input file name].
make clean: Removes all the files created in the compilation process and the exexutable.

test directory: There is a folder with simple and comlicated test txt files that cover all cases.
