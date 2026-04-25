# Balis Fotios Marios csd4958

all:
	flex scanner.l
	bison -d parser.y
	gcc lex.yy.c parser.tab.c symbol_table.c error.c -o parser

clean:
	rm -f parser
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
