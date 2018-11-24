all:	tigger

tigger:	eeyore.lex eeyore.y
	bison -d -y eeyore.y
	flex eeyore.lex
	gcc -c y.tab.h list.h tree.h bb.h y.tab.c lex.yy.c list.c tree.c bb.c
	gcc y.tab.o lex.yy.o tree.o bb.o list.o -o $@ -lm

clean:
	rm -rf tigger *.o lex.yy.* y.tab.* *.gch
