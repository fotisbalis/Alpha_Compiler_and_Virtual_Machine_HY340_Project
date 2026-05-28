# Balis Fotios Marios csd4958

all:
	flex scanner.l
	bison -d parser.y
	gcc *.c -o ../alpha_compiler

clean:
	rm -f ../alpha_compiler
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f ../symbol_table.txt
	rm -f ../syntax_rules.txt
	rm -f ../quads.txt
	rm -f ../instructions.txt
	rm -f ../alpha.abc
