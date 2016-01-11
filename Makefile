CPP = g++ --std=c++14 -I .

CURSES = -lcurses

all: encrypt

encrypt: encrypt.o RandomEncryptionMethod.o security/EncryptionMethod.hpp CommonTools.o
	$(CPP) encrypt.o RandomEncryptionMethod.o CommonTools.o -o encrypt $(CURSES)

encrypt.o: encrypt.cpp
	$(CPP) -c encrypt.cpp

RandomEncryptionMethod.o: security/RandomEncryptionMethod.hpp security/RandomEncryptionMethod.cpp \
		util/CommonTools.hpp
	$(CPP) -c security/RandomEncryptionMethod.cpp

CommonTools.o: util/CommonTools.hpp util/CommonTools.cpp
	$(CPP) -c util/CommonTools.cpp

clean:
	rm -f *.o *~ encrypt

