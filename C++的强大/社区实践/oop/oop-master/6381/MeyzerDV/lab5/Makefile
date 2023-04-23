CMPKEYS = -std=c++11 -static -Wall
BLDPATH = ./Build

all: dir $(BLDPATH)/Shape.o $(BLDPATH)/Circle.o $(BLDPATH)/Pentagon.o $(BLDPATH)/RegPentagon.o $(BLDPATH)/shared_ptr.o $(BLDPATH)/vector.o  $(BLDPATH)/main.o
	g++ $(BLDPATH)/*.o -o $(BLDPATH)/out $(CMPKEYS)
dir:
	mkdir -p $(BLDPATH)
$(BLDPATH)/main.o: main.cpp $(BLDPATH)/Shape.o $(BLDPATH)/Circle.o $(BLDPATH)/Pentagon.o $(BLDPATH)/RegPentagon.o $(BLDPATH)/shared_ptr.o $(BLDPATH)/vector.o
	g++ main.cpp -c -o $(BLDPATH)/main.o $(CMPKEYS)
$(BLDPATH)/Shape.o: Shape.cpp Shape.hpp Vectors.hpp
	g++ Shape.cpp -c -o $(BLDPATH)/Shape.o $(CMPKEYS)
$(BLDPATH)/Circle.o: $(BLDPATH)/Shape.o Circle.cpp Circle.hpp
	g++ Circle.cpp -c -o $(BLDPATH)/Circle.o $(CMPKEYS)
$(BLDPATH)/Pentagon.o: $(BLDPATH)/Shape.o Pentagon.cpp Pentagon.hpp
	g++ Pentagon.cpp -c -o $(BLDPATH)/Pentagon.o $(CMPKEYS)
$(BLDPATH)/RegPentagon.o: $(BLDPATH)/Shape.o RegPentagon.cpp RegPentagon.hpp
	g++ RegPentagon.cpp -c -o $(BLDPATH)/RegPentagon.o $(CMPKEYS)
$(BLDPATH)/shared_ptr.o: shared_ptr.cpp
	g++ shared_ptr.cpp -c -o $(BLDPATH)/shared_ptr.o $(CMPKEYS)
$(BLDPATH)/vector.o: vector.cpp
	g++ vector.cpp -c -o $(BLDPATH)/vector.o $(CMPKEYS)
