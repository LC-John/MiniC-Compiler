all:	tigger

tigger:	eeyore.lex eeyore.y
	bison -d -y eeyore.y
	flex eeyore.lex
	gcc -c y.tab.h y.tab.c lex.yy.c
	gcc y.tab.o lex.yy.o -o $@ -lm

clean:
	rm -rf tigger *.o lex.yy.* y.tab.* *.gch
