#ifndef ENCRYPTION_METHOD_HPP__
#define ENCRYPTION_METHOD_HPP__

#include <string>

class EncryptionMethod
{
    public:
        virtual void encrypt(const std::string &filename) const = 0;
};

#endif
