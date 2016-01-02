#include "RandomEncryptionMethod.h"

#include <iostream>
#include <string>

using namespace std;

RandomEncryptionMethod::RandomEncryptionMethod(const std::string &password)
        : mPassword(password) {}

RandomEncryptionMethod::RandomEncryptionMethod(std::string &&password)
        : mPassword(move(password)) {}

void RandomEncryptionMethod::encrypt(const string &filename) const
{
    cout << filename << endl;
}

