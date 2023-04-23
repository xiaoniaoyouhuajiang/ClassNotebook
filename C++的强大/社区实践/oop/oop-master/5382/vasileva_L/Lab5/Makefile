all: link 

test: Unittest_shapes.cpp oop_lr5.cpp oop_lr2.h 
	g++ -std=c++11 Unittest_shapes.cpp -c -o test.o
	g++ -std=c++11 oop_lr5.cpp -c -o demo.o  

oop_lr2: oop_lr2.cpp oop_lr2.h
	g++ -std=c++11 oop_lr2.cpp -c -o oop_lr2.o 

link: test oop_lr2 test.o demo.o oop_lr2.o
	g++ -std=c++11 test.o oop_lr2.o -lgtest -o lr5_test
	g++ -std=c++11 demo.o oop_lr2.o -o lr5_demo
	rm test.o oop_lr2.o
	rm demo.o oop_lr2.o

