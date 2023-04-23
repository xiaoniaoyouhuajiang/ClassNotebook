CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Alliance.cpp GameField.cpp Magicians.cpp Orcs.cpp Shooter.cpp Unit.cpp Elf.cpp Goblin.cpp Peon.cpp Troll.cpp Witch.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
