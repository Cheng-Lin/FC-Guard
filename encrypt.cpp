#include "security/EncryptionMethod.hpp"
#include "security/RandomEncryptionMethod.hpp"

#include <curses.h>
#include <iostream>
#include <string>

using namespace std;

string getPassword(const char *prompt)
{
    printw(prompt);
    noecho();

    char buff[256];
    getnstr(buff, sizeof(buff));

    echo();
    return buff;
}

int main(int argc, const char* argv[])
{
    string filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        cout << "Please provide the name of the file you want to encrypt: " << endl;
        getline(cin, filename);
    }

    initscr();
    string password;
    bool notSame = false;
    do {
        if (notSame) {
            printw("\nPassword entered does not match, pelase try again.\n");
        }
        password = getPassword("Please enter a password: ");
        notSame = password.compare(getPassword("Please re-enter the password: ")) != 0;
    } while (notSame);
    endwin();

    EncryptionMethod* encryptor = new RandomEncryptionMethod(password);
    encryptor->encrypt(filename);

    delete encryptor;
    return 0;
}

