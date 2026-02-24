Balis Fotios Marios csd4958

Project - Phase 1

The programme implements a lexical analyzer, recognizing the tokens from the input with regular expression using flex and putting them in a single linked list of tokens.

The Tokens are recognized with priority from highest to lowest: single line comment < block comment < nested comment < string < punctuation < keyword < opertator < real constant < integer constsnt < id.

The files used for the implementation are:
scanner.l (flex file that recognizes the tokens)
scanner.c (.c file that puts the tokens in single linked list and then goes through the list and prints them) 
token.h (struct Token that is used for each token)

Makefile:
make all: Compiles the flex file to create lex.yy.c and then the lex.yy.c with the scanner.c file to create "scanner" executable. Then run as ./scanner [input file name].
make clean: Remove lex.yy.c and scanner.

Machine tested on: funduki
