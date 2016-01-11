#include "RandomEncryptionMethod.h"

#include <functional>
#include <iostream>
#include <random>
#include <string>

using namespace std;

RandomEncryptionMethod::RandomEncryptionMethod(const std::string &password)
        : mPasswordHash(hash<string>()(password)) {}

void RandomEncryptionMethod::encrypt(const string &filename) const
{
    default_random_engine generator(static_cast<unsigned int>(mPasswordHash));
    uniform_int_distribution<unsigned int> distribution;

    for (int i = 0; i < 10; ++i) {
        int num = distribution(generator);
        char* carry = (char *)&num;
        cout << carry[0] << carry[1] << carry[2] << carry[3] << 'K';
    }
}

