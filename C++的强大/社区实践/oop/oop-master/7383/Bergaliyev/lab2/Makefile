all: main.o shape.o square.o trapeze.o isosceles_trapeze.o
	g++ main.o square.cpp shape.o trapeze.o isosceles_trapeze.o -o shapes
main.o: main.cpp shape.hpp square.hpp trapeze.hpp isosceles_trapeze.hpp
	g++ main.cpp -c
shape.o: shape.cpp shape.hpp
	g++ shape.cpp -c
square.o: square.cpp square.hpp
	g++ square.cpp -c
trapeze.o: trapeze.cpp trapeze.hpp
	g++ trapeze.cpp -c
isosceles_trapeze.o: isosceles_trapeze.cpp isosceles_trapeze.hpp
	g++ isosceles_trapeze.cpp -c
