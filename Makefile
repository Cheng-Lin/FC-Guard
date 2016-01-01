CPP = g++

CURSES = -lcurses

all: encrypt

encrypt: encrypt.o
	$(CPP) encrypt.o -o encrypt $(CURSES)

encrypt.o: encrypt.cpp
	$(CPP) -c encrypt.cpp

clean:
	rm -f *.o *~ encrypt

