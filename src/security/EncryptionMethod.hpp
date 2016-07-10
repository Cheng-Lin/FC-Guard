#ifndef ENCRYPTION_METHOD_HPP__
#define ENCRYPTION_METHOD_HPP__

#include <string>

class EncryptionMethod
{
    public:
        virtual void encrypt(const std::string &filename, const bool &force,
                const bool &removefile) const = 0;
        virtual void decrypt(const std::string &filename, const bool &force,
                bool removefile) const = 0;
};

#endif
