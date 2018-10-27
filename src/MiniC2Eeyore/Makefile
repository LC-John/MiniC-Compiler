all:    minic

minic:   minic.lex minic.y tree.h tree.c
	bison -d -y minic.y
	flex minic.lex
	gcc -c tree.h tree.c symtab.h symtab.c error.h error.c transform.h transform.c y.tab.h y.tab.c lex.yy.c
	gcc tree.o symtab.o error.o transform.o y.tab.o lex.yy.o -o $@ -lm

clean:
	rm -rf minic *.o lex.yy.* y.tab.* *.gch
