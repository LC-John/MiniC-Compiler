all:	minic2eeyore

minic2eeyore:	minic.lex minic.y tree.h tree.c symtab.h symtab.c error.h error.c transform.h transform.c
	bison -d -y minic.y
	flex minic.lex
	gcc -c tree.h tree.c symtab.h symtab.c error.h error.c transform.h transform.c y.tab.h y.tab.c lex.yy.c
	gcc tree.o symtab.o error.o transform.o y.tab.o lex.yy.o -o $@ -lm

clean:
	rm -rf eeyore *.o lex.yy.* y.tab.* *.gch null.minic
	rm -rf test_cases/*
