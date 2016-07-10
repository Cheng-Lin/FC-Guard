#ifndef RANDOM_ENCRYPTION_METHOD_HPP__
#define RANDOM_ENCRYPTION_METHOD_HPP__

#include "EncryptionMethod.hpp"
#include <string>

class RandomEncryptionMethod : public EncryptionMethod
{
    public:
        RandomEncryptionMethod(const std::string &password);
        RandomEncryptionMethod(const RandomEncryptionMethod &) = delete;

        RandomEncryptionMethod &operator=(const RandomEncryptionMethod &) = delete;

        ~RandomEncryptionMethod() = default;

        void encrypt(const std::string &filename, const bool &force = false,
                const bool &removefile = false) const;
        void decrypt(const std::string &filename, const bool &force = false,
                bool removefile = false) const;

        static const std::string METADATA_KEY;
        static const std::string METADATA_VALUE_ENCRYPT;
        static const std::string METADATA_VALUE_DECRYPT;

    private:
        void encryption_helper(const std::string &finName, const std::string &foutName,
                const bool &encrypt, const bool &removefile) const;
        void clean_up(const std::string &finName, const std::string &foutName,
                const std::string &meatadata, const bool &removefile) const;
        unsigned int getSeed(const std::string uuid = "") const;

        static const std::string ENCRYPT_EXTENSION;
        static const std::string DECRYPT_EXTENSION;
        static const std::size_t UUID_SIZE;

        const bool IS_LITTLE_ENDIAN;
        const std::string PASSWORD;
};

#endif
