last: main.o algs.o test.o
	g++ main.o -o last algs.o
	g++ test.o -o test algs.o
	rm *.o
main.o: main.cpp
	g++ -c -std=c++11 main.cpp
algs.o: algs.cpp algs.hpp
	g++ -c  -std=c++11 algs.cpp
test.o: test.cpp
	g++ -c -std=c++11 test.cpp
