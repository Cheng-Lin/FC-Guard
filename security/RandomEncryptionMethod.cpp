#include "RandomEncryptionMethod.hpp"
#include "util/CommonTools.hpp"
#include "util/InterfaceTools.hpp"

#include <algorithm>
#include <boost/format.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstring>
#include <errno.h>
#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <sys/types.h>
#include <sys/xattr.h>

using namespace std;
namespace uuids = boost::uuids;

const string RandomEncryptionMethod::METADATA_KEY = "user.encrypted";
const string RandomEncryptionMethod::METADATA_VALUE_ENCRYPT = "y";
const string RandomEncryptionMethod::METADATA_VALUE_DECRYPT = "n";

const string RandomEncryptionMethod::ENCRYPT_EXTENSION = ".enc";
const string RandomEncryptionMethod::DECRYPT_EXTENSION = ".dec";

const size_t RandomEncryptionMethod::UUID_SIZE = uuids::to_string(uuids::nil_uuid()).size();

RandomEncryptionMethod::RandomEncryptionMethod(const string &password)
        : PASSWORD(password), IS_LITTLE_ENDIAN(CommonTools::IsLittleEndian())
{
}

void RandomEncryptionMethod::encrypt(const string &filename, const bool &force,
        const bool &removefile) const
{
    this->encryption_helper(filename, filename + RandomEncryptionMethod::ENCRYPT_EXTENSION, true,
            removefile);
}

void RandomEncryptionMethod::decrypt(const string &filename, const bool &force,
        bool removefile) const
{
    string extension = filename.substr(filename.length()
            - RandomEncryptionMethod::ENCRYPT_EXTENSION.length());
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    string foutName = filename + RandomEncryptionMethod::DECRYPT_EXTENSION;
    if (RandomEncryptionMethod::ENCRYPT_EXTENSION.compare(extension) == 0)
    {
        string temp = filename.substr(0, filename.length()
                - RandomEncryptionMethod::ENCRYPT_EXTENSION.length());
        if (force || !experimental::filesystem::exists(temp) ||
                InterfaceTools::GetConfirmation("[WARN] Decrypt file destination [" + temp +
                    "] already exist. Overwrite?"))
        {
            foutName = temp;
        }
    }
    else
    {
        cout << boost::format("[WARN] File [%s] does not have encrypted extension [%s].") %
                filename % RandomEncryptionMethod::ENCRYPT_EXTENSION << endl;
        if (removefile)
        {
            foutName = filename;
            removefile = false;
        }
        else if (force || InterfaceTools::GetConfirmation("Overwrite input file?"))
        {
            foutName = filename;
        }
    }

    this->encryption_helper(filename, foutName, false, removefile);
}

void RandomEncryptionMethod::encryption_helper(const string &finName, const string &foutName,
        const bool &encrypt, const bool &removefile) const
{
    ifstream fin(finName, ifstream::binary);
    size_t fileSize = CommonTools::GetFileSize(fin);

    string uuid;
    if (encrypt) {
        uuid = uuids::to_string(uuids::random_generator()());
    } else {
        if (fileSize < RandomEncryptionMethod::UUID_SIZE) {
            cerr << finName << " does not contain valid encrypted data" << endl;
            return;
        }

        char *temp = new char[RandomEncryptionMethod::UUID_SIZE];
        fin.read(temp, RandomEncryptionMethod::UUID_SIZE);
        temp[RandomEncryptionMethod::UUID_SIZE] = '\0';
        uuid = temp;

        fileSize -= RandomEncryptionMethod::UUID_SIZE;
        delete [] temp;
    }
    cout << uuid << endl;
    default_random_engine generator(this->getSeed(uuid));
    uniform_int_distribution<unsigned int> distribution;

    char *data = new char[fileSize];
    fin.read(data, fileSize);
    fin.close();

    ofstream fout(foutName, ofstream::binary);
    if (encrypt) {
        fout.write(uuid.c_str(), RandomEncryptionMethod::UUID_SIZE);
    }

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

    if (encrypt) {
        this->clean_up(finName, foutName, RandomEncryptionMethod::METADATA_VALUE_ENCRYPT,
                removefile);
    } else {
        this->clean_up(finName, foutName, RandomEncryptionMethod::METADATA_VALUE_DECRYPT,
                removefile);
    }
}

void RandomEncryptionMethod::clean_up(const string &finName, const string &foutName,
        const string &metadata, const bool &removefile) const
{
    if (setxattr(foutName.c_str(), RandomEncryptionMethod::METADATA_KEY.c_str(),
            metadata.c_str(), metadata.size(), XATTR_CREATE) == -1)
    {
        if (setxattr(foutName.c_str(), RandomEncryptionMethod::METADATA_KEY.c_str(),
                metadata.c_str(), metadata.size(), XATTR_REPLACE) == -1)
        {
            cerr << strerror(errno) << endl;
            return;
        }
    }

    if (removefile) {
        remove(finName.c_str());
    }
}

unsigned int RandomEncryptionMethod::getSeed(const std::string uuid) const
{
    size_t passwordHash = hash<string>()(this->PASSWORD + uuid);
    return static_cast<unsigned int>(passwordHash & 0xffffffff);
}

