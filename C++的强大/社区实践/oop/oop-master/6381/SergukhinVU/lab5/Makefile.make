all: lab5
lab5: shape.o main.o
	g++ main.o shape.o -o lab5 -std=c++11

shape.o: shape.cpp
	g++ -c shape.cpp -std=c++11
main.o: main.cpp
	g++ -c main.cpp -std=c++11