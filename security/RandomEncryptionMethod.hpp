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

        void encrypt(const std::string &filename) const;
        void decrypt(const std::string &filename, const bool &overwrite) const;

    private:
        void encryption_helper(const std::string &finName, const std::string &foutName) const;
        unsigned int getSeed() const;

        static const std::string ENCRYPT_EXTENSION;
        static const std::string DECRYPT_EXTENSION;

        const bool IS_LITTLE_ENDIAN;
        const std::size_t PASSWORD_HASH;
};

#endif
