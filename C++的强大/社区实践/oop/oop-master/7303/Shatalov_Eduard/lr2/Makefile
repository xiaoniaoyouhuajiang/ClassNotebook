all: main


main: main.o ellipse.o sector.o shape.o star.o
	g++ main.o ellipse.o sector.o shape.o star.o -o main

ellipse.o: ellipse.cpp ellipse.h shape.h
	g++ -c ellipse.cpp ellipse.h shape.h

sector.o: sector.cpp sector.h shape.h
	g++ -c sector.cpp sector.h shape.h

shape.o: shape.cpp shape.h
	g++ -c shape.cpp shape.h

star.o: star.cpp star.h shape.h
	g++ -c star.cpp shape.h star.h

main.o: main.cpp star.h sector.h ellipse.h shape.h
	g++ -c main.cpp star.h sector.h ellipse.h shape.h
