CC=g++
CFLAGS=-c -w -O3 -std=c++17
LDFLAGS=
SRC=sources
TST=tests
SOURCES=main.cpp $(SRC)/unit.cpp $(SRC)/map.cpp \
$(SRC)/object.cpp $(SRC)/game.cpp $(SRC)/objectfactory.cpp $(SRC)/stuff.cpp $(SRC)/objectstorage.cpp \
$(SRC)/base.cpp $(SRC)/neutral.cpp $(SRC)/facade.cpp $(SRC)/parser.cpp $(SRC)/logger.cpp \
$(SRC)/serializer.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f main.o sources/*.o tests/*.o