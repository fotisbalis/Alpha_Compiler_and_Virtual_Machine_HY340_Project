Balis Fotios Marios csd4958

The project implements a compiler and a virtual machine for the Alpha programming language (similar to Javascript).
The language used for the implementation is c alongside Flex for lexical analysis and Yacc Bison for syntactical analysis.

How to compile:
You need to run in an environment where Flex and Yacc Bison are installed (run $sudo apt install flex, $sudo apt install bison byacc)
To compile the entire project run $make all
To compile only the compiler run $make compiler
To compile only the virtual machine run $make vm
To clean all the compile time and runtime created files run $make clean

How to run the compiler:
run $./alpha_compiler [input file]

Compiler output:
If compilation is not successful, the console output will be the existing errors.
If compilation is successful, then the following files are created:
quads.txt (assembly like intermediate code)
instructions.txt (target code)
symbol_table.txt (symbol table content)
syntax_rules.txt (grammar reduce rules used for the syntactical analysis)
alpha.abc (binary version of instructions.txt and input of the virtual machine)

How to run the virtual machine:
run $./alpha_vm alpha.abc

Virtual Machine output:
The final output of the input file
