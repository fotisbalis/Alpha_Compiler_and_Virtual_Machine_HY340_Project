Balis Fotios Marios csd4958

Project - Phase 3

Machine tested on: funduki.

The program implements intermediate code generation. It converts the input to assembly like quads. The quads are only generated if the parsing of the grammar completes with no syntx errors.
In case of semantic errors, the quads are generated except for the part of the code where the error occurs.

Makefile:
make all: Compiles the flex file, then the bison file and then all the .c files together to create the "parser" executable. Then run as ./parser [input file name].
make clean: Removes all the files created in the compilation process, the exexutable and the quads.txt file.

Output:
The generated quads are in the "quads.txt" file. The console output remains the same as Phase 2 with the grammar reductions, erros and symbol table.
