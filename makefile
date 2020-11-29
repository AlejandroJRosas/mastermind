CC = gcc -Wall
OBJECTS = source/main.o source/mtmlib.o

juego: all clean

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o juego

source/main.o:	source/mtmlib.h
source/mtmlib.o: source/mtmlib.h

.PHONY: clean
clean:
	rm -rf source/*.o