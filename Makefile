# Makefile to build monte_pi_sprng program
# --- macros
CC=g++
CFLAGS= -I/usr/include -g
OBJECTS= BejeweledIO.o BejeweledMain.o GameBoard.o
LIBS= -lfltk
APPNAME=bejeweled


# --- targets
all: bejeweled
bejeweled: $(OBJECTS) 
	$(CC) -o $(APPNAME) $(OBJECTS) $(LIBS)
           
BejeweledIO.o: BejeweledIO.cpp
	$(CC) $(CLFAGS) -c BejeweledIO.cpp

BejeweledMain.o: BejeweledMain.cpp
	$(CC) $(CLFAGS) -c BejeweledMain.cpp

GameBoard.o: GameBoard.cpp
	$(CC) $(CLFAGS) -c GameBoard.cpp

#.cpp.o: 
#	$(CC) $(CFLAGS) -c $<

# --- remove binary and executable files
clean:
	rm -f $(APPNAME) $(OBJECTS)
