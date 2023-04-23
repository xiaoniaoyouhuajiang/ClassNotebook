all: lab5.o Shape.o
	g++ -std=c++11 lab5.o Shape.o -o lab5
lab5.o: lab5.cpp
	g++ -std=c++11 lab5.cpp -c
Shape.o: Shape.hpp Shape.cpp
	g++ -std=c++11 Shape.cpp -c