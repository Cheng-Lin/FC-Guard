#include "security/EncryptionMethod.hpp"
#include "security/RandomEncryptionMethod.hpp"
#include "util/InterfaceTools.hpp"

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

	cout << "Do you wish to overwrite the existing unencrypted file(s)? [y/n]";
	string line;
	getline(cin, line);
	bool overwrite = (line.compare("y") == 0) || (line.compare("Y") == 0);

    string password = InterfaceTools::GetPassword("Please enter a password: ");

    EncryptionMethod* decryptor = new RandomEncryptionMethod(password);
    decryptor->decrypt(filename, overwrite);

    delete decryptor;
    return 0;
}

