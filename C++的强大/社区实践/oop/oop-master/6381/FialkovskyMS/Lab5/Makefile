SRC=Source
BLD=Build
LIB=-lsfml-system-2 -lsfml-window-2 -lsfml-graphics-2
LIB_HPP=$(SRC)/SFML/Graphics.hpp $(SRC)/SFML/Window/VideoMode.hpp $(SRC)/SFML/Graphics/Shape.hpp

all: $(BLD)/MyShape.o $(BLD)/MySquare.o $(BLD)/MyRhombus.o $(BLD)/MyTrapeze.o $(BLD)/ObjectID.o $(BLD)/main.o $(LIB_HPP)
	g++ $(BLD)/MyShape.o $(BLD)/MySquare.o $(BLD)/MyRhombus.o $(BLD)/MyTrapeze.o $(BLD)/ObjectID.o $(BLD)/main.o -o Lab.exe $(LIB)

$(BLD)/main.o: $(SRC)/main.cpp
	g++ -c $(SRC)/main.cpp -o $(BLD)/main.o

$(BLD)/ObjectID.o: $(SRC)/ObjectID.cpp $(SRC)/ObjectID.hpp
	g++ -c $(SRC)/ObjectID.cpp -o $(BLD)/ObjectID.o

$(BLD)/MyShape.o: $(SRC)/MyShape.cpp $(SRC)/MyShape.hpp
	g++ -c $(SRC)/MyShape.cpp -o $(BLD)/MyShape.o
	
$(BLD)/MySquare.o: $(SRC)/MySquare.cpp $(SRC)/MySquare.hpp
	g++ -c $(SRC)/MySquare.cpp -o $(BLD)/MySquare.o
		
$(BLD)/MyRhombus.o: $(SRC)/MyRhombus.cpp $(SRC)/MyRhombus.hpp
	g++ -c $(SRC)/MyRhombus.cpp -o $(BLD)/MyRhombus.o
	
$(BLD)/MyTrapeze.o: $(SRC)/MyTrapeze.cpp $(SRC)/MyTrapeze.hpp
	g++ -c $(SRC)/MyTrapeze.cpp -o $(BLD)/MyTrapeze.o

