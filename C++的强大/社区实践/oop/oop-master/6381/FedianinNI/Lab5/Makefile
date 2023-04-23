final: Shape.o Ellipse.o Circle.o Curve.o main.o algorithms.o testing.o
	g++ Shape.o Ellipse.o Circle.o Curve.o main.o testing.o -o final algorithms.o
	rm *.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
algorithms.o: algorithms.cpp algorithms.hpp
	g++ -std=c++11 -c algorithms.cpp
Ellipse.o: Ellipse.cpp
	g++ -std=c++11 -c Ellipse.cpp
Circle.o: Circle.cpp Circle.hpp
	g++ -std=c++11 -c Circle.cpp
Curve.o: Curve.cpp Curve.hpp
	g++ -std=c++11 -c Curve.cpp
Shape.o: Shape.cpp Shape.hpp
	g++ -std=c++11 -c Shape.cpp
testing.o: testing.cpp testing.hpp
	g++ -std=c++11 -c testing.cpp