all: Lab5
Lab5: Lab5.o Shape.o Square.o Right_Triangle.o Isosceles_triangle.o Vector.o Shared_ptr.o 
	g++ Lab5.o Shape.o Square.o Right_Triangle.o Isosceles_triangle.o Vector.o Shared_ptr.o -o Lab5
	
Square.o: Square.cpp
	g++ -c Square.cpp
	
Right_Triangle.o: Right_Triangle.cpp
	g++ -c Right_Triangle.cpp
	
Isosceles_triangle.o: Isosceles_triangle.cpp
	g++ -c Isosceles_triangle.cpp
	
Shape.o: Shape.cpp
	g++ -c Shape.cpp
	
Vector.o: Vector.cpp
	g++ -c Vector.cpp
	
Shared_ptr.o: Shared_ptr.cpp
	g++ -c Shared_ptr.cpp -o Shared_ptr.o
	
Lab5.o: Lab5.cpp
	g++ -c Lab5.cpp
	
clean:
	rm -rf *.o Lab5