all: build

removeBin: test
	rm -rf test

build: link removeObjF

removeObjF: figure.o test.o
	rm -rf figure.o test.o

link: figureComp testComp
	g++ -std=c++11 -o test -lgtest figure.o test.o 

figureComp: figure.h figure.cpp
	g++ -std=c++11 -o figure.o figure.cpp -c

testComp: test.cpp figure.h
	g++ -std=c++11 -o test.o test.cpp -c
