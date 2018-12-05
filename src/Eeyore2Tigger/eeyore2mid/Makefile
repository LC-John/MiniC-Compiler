all : eeyore2mid

eeyore2mid : flex bison main.cpp tree.cpp count.cpp symtab.cpp
	g++ -o eeyore2mid tree.cpp count.cpp main.cpp symtab.cpp eeyore2mid.tab.c lex.yy.c -g --std=c++14

flex : eeyore2mid.l bison
	flex eeyore2mid.l

bison : eeyore2mid.y
	bison eeyore2mid.y -d

clean:
	rm eeyore2mid.tab.h eeyore2mid.tab.c lex.yy.c eeyore2mid
