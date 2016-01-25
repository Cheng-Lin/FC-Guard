CPP = g++ --std=c++14 -I .

CURSES = -lcurses
FS_TS = -lstdc++fs

all: encrypt decrypt

encrypt: encrypt.o RandomEncryptionMethod.o security/EncryptionMethod.hpp CommonTools.o \
		InterfaceTools.o
	$(CPP) encrypt.o RandomEncryptionMethod.o CommonTools.o InterfaceTools.o -o encrypt \
			$(CURSES) $(FS_TS)

decrypt: decrypt.o RandomEncryptionMethod.o security/EncryptionMethod.hpp CommonTools.o \
		InterfaceTools.o
	$(CPP) decrypt.o RandomEncryptionMethod.o CommonTools.o InterfaceTools.o -o decrypt \
			$(CURSES) $(FS_TS)

encrypt.o: encrypt.cpp
	$(CPP) -c encrypt.cpp

decrypt.o: decrypt.cpp
	$(CPP) -c decrypt.cpp

RandomEncryptionMethod.o: security/RandomEncryptionMethod.hpp security/RandomEncryptionMethod.cpp \
		util/CommonTools.hpp
	$(CPP) -c security/RandomEncryptionMethod.cpp

CommonTools.o: util/CommonTools.hpp util/CommonTools.cpp
	$(CPP) -c util/CommonTools.cpp

InterfaceTools.o: util/InterfaceTools.hpp util/InterfaceTools.cpp
	$(CPP) -c util/InterfaceTools.cpp

clean:
	rm -f *.o *~ encrypt decrypt

