#include "security/EncryptionMethod.hpp"
#include "security/RandomEncryptionMethod.hpp"
#include "util/InterfaceTools.hpp"

#include <curses.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[])
{
    string filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        cout << "Please provide the name of the file you want to encrypt: " << endl;
        getline(cin, filename);
    }

    string password;
    bool notSame = false;
    do {
        if (notSame) {
            printw("\nPassword entered does not match, pelase try again.\n");
        }
        password = InterfaceTools::GetPassword("Please enter a password: ");
        notSame = password.compare(InterfaceTools::GetPassword("Please re-enter the password: "))
                != 0;
    } while (notSame);

    EncryptionMethod* encryptor = new RandomEncryptionMethod(password);
    encryptor->encrypt(filename);

    delete encryptor;
    return 0;
}

