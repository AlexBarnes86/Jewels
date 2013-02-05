# Makefile to build monte_pi_sprng program
# --- macros
CC=g++
CFLAGS=-I/usr/include -Iinclude -g -c
OBJECTS=bin/BejeweledMain.o bin/BejeweledIO.o bin/BejeweledWindow.o bin/GameBoard.o
SOURCES=src/BejeweledMain.cpp src/Bejeweled.cpp.cpp src/BejeweledMain.cpp src/BejeweledWin.cppw.cpp src/Game.cppard.cpp
LIBS=-lfltk -lfltk_images
APPNAME=Jewels

# --- targets
all: jewels
jewels: $(OBJECTS)
	$(CC) -o $(APPNAME) $(OBJECTS) $(LIBS)
           
bin/BejeweledMain.o:
	$(CC) $(CFLAGS) src/BejeweledMain.cpp -o $@

bin/BejeweledIO.o: 
	$(CC) $(CFLAGS) src/BejeweledIO.cpp -o $@

bin/BejeweledWindow.o: 
	$(CC) $(CFLAGS) src/BejeweledWindow.cpp -o $@

bin/GameBoard.o: 
	$(CC) $(CFLAGS) src/GameBoard.cpp -o $@

# --- remove binary and executable files
clean:
	rm -f $(APPNAME) bin/*
