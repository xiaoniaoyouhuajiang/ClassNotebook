result: main.o AlgorithmsForShapes.o test.o
	g++ main.o -o result.out AlgorithmsForShapes.o test.o
	rm *.o
	./result.out
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
AlgorithmsForShapes.o: AlgorithmsForShapes.cpp AlgorithmsForShapes.h
	g++ -std=c++11 -c AlgorithmsForShapes.cpp
test.o: test.cpp test.h
	g++ -std=c++11 -c test.cpp
