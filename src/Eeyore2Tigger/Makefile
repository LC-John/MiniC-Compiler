all: tiggerC.cpp sdriver.cpp
	(cd minic2eeyore; make)
	(cd eeyore2mid; make)
	(cd mid2tigger; make)
	g++ -o tiggerC tiggerC.cpp
	g++ -o sdriver sdriver.cpp
clean:
	(cd minic2eeyore; make clean)
	(cd eeyore2mid; make clean)
	(cd mid2tigger; make clean)
	rm tiggerC
	rm sdriver
	rm -rf *.log
	rm -rf *.out
	rm -rf null.minic
