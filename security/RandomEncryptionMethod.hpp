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
        const std::size_t mPasswordHash;
};

#endif
