#include "RandomEncryptionMethod.hpp"
#include "util/CommonTools.hpp"

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>

using namespace std;

const string RandomEncryptionMethod::ENCRYPT_EXTENSION = ".enc";
const string RandomEncryptionMethod::DECRYPT_EXTENSION = ".dec";

RandomEncryptionMethod::RandomEncryptionMethod(const string &password)
        : PASSWORD_HASH(hash<string>()(password)), IS_LITTLE_ENDIAN(CommonTools::IsLittleEndian())
{
}

void RandomEncryptionMethod::encrypt(const string &filename) const
{
    this->encryption_helper(filename, filename + RandomEncryptionMethod::ENCRYPT_EXTENSION);
}

void RandomEncryptionMethod::decrypt(const string &filename, const bool &overwrite) const
{
    string extension = filename.substr(filename.length()
            - RandomEncryptionMethod::ENCRYPT_EXTENSION.length());
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    string foutName = filename + RandomEncryptionMethod::DECRYPT_EXTENSION;
    if (RandomEncryptionMethod::ENCRYPT_EXTENSION.compare(extension) == 0)
    {
        string temp = filename.substr(0, filename.length()
                - RandomEncryptionMethod::ENCRYPT_EXTENSION.length());
        if (overwrite || !experimental::filesystem::exists(temp))
        {
            foutName = temp;
        }
    }

    this->encryption_helper(filename, foutName);
}

void RandomEncryptionMethod::encryption_helper(const string &finName, const string &foutName) const
{
    ifstream fin(finName, ifstream::binary);
    ofstream fout(foutName, ofstream::binary);

    default_random_engine generator(this->getSeed());
    uniform_int_distribution<unsigned int> distribution;

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

