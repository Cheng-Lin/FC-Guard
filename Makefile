CPP = g++ --std=c++14

CURSES = -lcurses

all: encrypt

encrypt: encrypt.o RandomEncryptionMethod.o security/EncryptionMethod.h
	$(CPP) encrypt.o RandomEncryptionMethod.o -o encrypt $(CURSES)

encrypt.o: encrypt.cpp
	$(CPP) -c encrypt.cpp

RandomEncryptionMethod.o: security/RandomEncryptionMethod.h security/RandomEncryptionMethod.cpp
	$(CPP) -c security/RandomEncryptionMethod.cpp

clean:
	rm -f *.o *~ encrypt

