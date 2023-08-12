CC = gcc -Wall
OBJECTS = source/main.o source/mtmlib.o

juego: all clear

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o juego

source/main.o:	source/mtmlib.h
source/mtmlib.o: source/mtmlib.h

.PHONY: clear
clear:
	rm -rf source/*.o