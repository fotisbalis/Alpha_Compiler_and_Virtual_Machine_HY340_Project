# Balis Fotios Marios csd4958

all:
	flex scanner.l
	bison -d parser.y
	gcc *.c -o compiler

clean:
	rm -f compiler
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f quads.txt
	rm -f instructions.txt
	rm -f alpha.abc
