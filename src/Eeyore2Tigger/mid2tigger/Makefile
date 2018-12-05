all : mid2tigger

mid2tigger : flex bison main.cpp tree.cpp symtab.cpp flowgraph.cpp conflictgraph.cpp
	g++ -o mid2tigger main.cpp tree.cpp symtab.cpp flowgraph.cpp conflictgraph.cpp mid2tigger.tab.c lex.yy.c -g -std=c++14

flex : mid2tigger.l bison
	flex mid2tigger.l

bison : mid2tigger.y
	bison mid2tigger.y -d

clean:
	rm mid2tigger.tab.h mid2tigger.tab.c lex.yy.c mid2tigger
