CC = g++
CFLAGS = -c -Wall

all: main

main: shape.o square.o  star.o pentagon.o lab2.o
	$(CC) shape.o square.o  star.o pentagon.o lab2.o -o main

shape.o: shape.h shape.cpp
	$(CC) $(CFLAGS) shape.h shape.cpp 

square.o: square.h square.cpp
	$(CC) $(CFLAGS) square.h square.cpp 

star.o: star.h star.cpp
	$(CC) $(CFLAGS) star.h star.cpp 

pentagon.o: pentagon.h pentagon.cpp
	$(CC) $(CFLAGS) pentagon.h pentagon.cpp

lab2.o: lab2.cpp
	$(CC) $(CFLAGS) lab2.cpp 

clean:
	rm -rf *.o *.gch main
