clear: all
	rm *.o
all: main.o RadiusVector.o Color.o Shapes.o
	g++ main.o RadiusVector.o Color.o Shapes.o -o lab_work2
main.o: src/main.cpp src/Shapes.h src/Color.h src/RadiusVector.h
	g++ -c src/main.cpp
RadiusVector.o: src/RadiusVector.cpp src/RadiusVector.h
	g++ -c src/RadiusVector.cpp
Color.o: src/Color.cpp src/Color.h
	g++ -c src/Color.cpp
Shapes.o: src/Shapes.cpp src/Shapes.h src/RadiusVector.h src/Color.h
	g++ -c src/Shapes.cpp
