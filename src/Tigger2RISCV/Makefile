all: merge.c
	(cd tigger2riscv; make)
	g++ -o riscv64C merge.c

clean:
	(cd tigger2riscv; make clean)
	rm -rf riscv64C
	rm -rf *.log
	rm -rf *.out
