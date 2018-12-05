all: merge.cpp
	(cd eeyore2mid; make)
	(cd mid2tigger; make)
	g++ -o tiggerC merge.cpp

clean:
	(cd eeyore2mid; make clean)
	(cd mid2tigger; make clean)
	rm tiggerC
	rm -rf *.log
	rm -rf *.out
	rm -rf null.minic
