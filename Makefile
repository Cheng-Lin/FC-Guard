CPP = g++ --std=c++14 -I .

BOOST = -lboost_system -lboost_filesystem -lboost_program_options
CURSES = -lcurses
FS_TS = -lstdc++fs -lpthread

all: encrypt decrypt

encrypt: encrypt.o RandomEncryptionMethod.o security/EncryptionMethod.hpp CommonTools.o \
		FileTools.o InterfaceTools.o
	$(CPP) encrypt.o RandomEncryptionMethod.o CommonTools.o FileTools.o InterfaceTools.o \
			-o encrypt $(BOOST) $(CURSES) $(FS_TS)

decrypt: decrypt.o RandomEncryptionMethod.o security/EncryptionMethod.hpp CommonTools.o \
		FileTools.o InterfaceTools.o
	$(CPP) decrypt.o RandomEncryptionMethod.o CommonTools.o FileTools.o InterfaceTools.o \
			-o decrypt $(BOOST) $(CURSES) $(FS_TS)

encrypt.o: encrypt.cpp
	$(CPP) -c encrypt.cpp

decrypt.o: decrypt.cpp
	$(CPP) -c decrypt.cpp

RandomEncryptionMethod.o: security/RandomEncryptionMethod.hpp security/RandomEncryptionMethod.cpp \
		util/CommonTools.hpp util/InterfaceTools.hpp
	$(CPP) -c security/RandomEncryptionMethod.cpp

CommonTools.o: util/CommonTools.hpp util/CommonTools.cpp
	$(CPP) -c util/CommonTools.cpp

FileTools.o: util/FileTools.hpp util/FileTools.cpp
	$(CPP) -c util/FileTools.cpp

InterfaceTools.o: util/InterfaceTools.hpp util/InterfaceTools.cpp
	$(CPP) -c util/InterfaceTools.cpp

clean:
	rm -f *.o *~ encrypt decrypt

