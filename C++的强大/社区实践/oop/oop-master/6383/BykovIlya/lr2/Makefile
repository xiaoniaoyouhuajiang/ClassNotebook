TARGET = lr2
PREFIX = /lr2

.PHONY: all clean install uninstall

all: $(TARGET)	
	
clean:
	rm -rf $(TARGET) *.o
main.o: main.cpp
	g++ -c -o main.o main.cpp
center.o: center.o center.cpp
	g++ -c -o center.o center.cpp
colour.o: colour.o colour.cpp
	g++ -c -o colour.o colour.cpp
isoscelesTriangle.o: isoscelesTriangle.o isoscelesTriangle.cpp
	g++ -c -o isoscelesTriangle.o isoscelesTriangle.cpp
polygon.o: polygon.o polygon.cpp
	g++ -c -o polygon.o polygon.cpp
rectangle.o: rectangle.o rectangle.cpp
	g++ -c -o rectangle.o rectangle.cpp
rightTriangle.o: rightTriangle.o rightTriangle.cpp
	g++ -c -o rightTriangle.o rightTriangle.cpp
shape.o: shape.cpp
	g++ -c -o shape.o shape.cpp
square.o: square.o square.cpp
	g++ -c -o square.o square.cpp
triangle.o: triangle.o triangle.cpp
	g++ -c -o triangle.o triangle.cpp
$(TARGET): main.o shape.o center.o colour.o isoscelesTriangle.o polygon.o rectangle.o rightTriangle.o square.o triangle.o
	g++ -o $(TARGET) main.o shape.o center.o colour.o isoscelesTriangle.o polygon.o rectangle.o rightTriangle.o square.o triangle.o
install:
	install $(TARGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)


