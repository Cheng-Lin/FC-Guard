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

    private:
        unsigned int getSeed() const;
        
        const bool IS_LITTLE_ENDIAN;
        const std::size_t PASSWORD_HASH;
};

#endif
