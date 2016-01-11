#include "RandomEncryptionMethod.hpp"
#include "util/CommonTools.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>

using namespace std;

RandomEncryptionMethod::RandomEncryptionMethod(const std::string &password)
        : PASSWORD_HASH(hash<string>()(password)), IS_LITTLE_ENDIAN(CommonTools::IsLittleEndian())
{
}

void RandomEncryptionMethod::encrypt(const string &filename) const
{
    default_random_engine generator(this->getSeed());
    uniform_int_distribution<unsigned int> distribution;

    ifstream fin(filename, ifstream::binary);
    ofstream fout(filename + ".enc", ofstream::binary);

    size_t fileSize = CommonTools::GetFileSize(fin);
    char *data = new char[fileSize];
    fin.read(data, fileSize);
    
    int step = 4;
    int intToCharRatio = sizeof(int) / sizeof(char);
    for (size_t i = 0; i < fileSize; i += 4) 
    {
        int num = distribution(generator);
        char* carry = (char *)&num;
        for (int j = 0; j < step && i + j < fileSize; ++j)
        {
            int index = IS_LITTLE_ENDIAN ? j : intToCharRatio - j - 1;
            if (carry[index] != 0)
            {
                data[i + j] ^= carry[index];
            }
        }
    }
    fout.write(data, fileSize);

    delete[] data;
    fout.close();
    fin.close();
}

unsigned int RandomEncryptionMethod::getSeed() const
{
    return static_cast<unsigned int>(this->PASSWORD_HASH & 0xffffffff);
}
