all:	tigger

tigger:	eeyore.lex eeyore.y
	bison -d -y eeyore.y
	flex eeyore.lex
	gcc -c y.tab.h tree.h y.tab.c lex.yy.c tree.c
	gcc y.tab.o lex.yy.o tree.o -o $@ -lm

clean:
	rm -rf tigger *.o lex.yy.* y.tab.* *.gch
