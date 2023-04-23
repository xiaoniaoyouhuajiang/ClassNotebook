final: main.o algorithms.o testing.o
	g++ main.o -o final algorithms.o testing.o
	rm *.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
algorithms.o: algorithms.cpp algorithms.hpp
	g++ -std=c++11 -c algorithms.cpp
testing.o: testing.cpp	testing.hpp
	g++ -std=c++11 -c testing.cpp