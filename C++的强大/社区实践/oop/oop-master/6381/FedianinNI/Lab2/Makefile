all: Shape

Shape: main.o Circle.o Curve.o Ellipse.o Shape.o
	g++ main.o Circle.o Curve.o Ellipse.o Shape.o -o Shape

main.o: main.cpp
	g++ -c main.cpp
	
Circle.o: Circle.cpp
	g++ -c Circle.cpp
	
Curve.o: Curve.cpp
	g++ -c Curve.cpp
	
Ellipse.o: Ellipse.cpp
	g++ -c Ellipse.cpp
	
Shape.o: Shape.cpp
	g++ -c Shape.cpp

clean:
	rm -rf *.o Shape