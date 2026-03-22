# Balis Fotios Marios csd4958

all:
	flex scanner.l
	bison -d parser.y
	gcc lex.yy.c parser.tab.c -o parser

clean:
	rm -f scanner
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
