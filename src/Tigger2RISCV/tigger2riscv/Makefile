all:	tigger2riscv

tigger2riscv:	bison flex main.cpp
	gcc -o $@ y.tab.c lex.yy.c main.cpp

bison:
	bison -d -y tigger2riscv.y

flex:	bison
	flex tigger2riscv.lex

clean:
	rm -rf y.tab.* lex.yy.* tigger2riscv
