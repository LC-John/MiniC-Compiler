all: merge.c
	(cd tigger2riscv; make)
	g++ -o riscvC merge.c

clean:
	(cd tigger2riscv; make clean)
	rm -rf riscvC
	rm -rf *.log
	rm -rf *.out
