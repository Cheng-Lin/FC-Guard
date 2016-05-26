#ifndef FILE_TOOLS_HPP__
#define FILE_TOOLS_HPP__

#include <string>
#include <vector>

class FileTools
{
    public:
        static std::vector<std::string> GetFileList(const std::string &path,
                const std::string &mKey, const std::string &mValue, const bool &reencrypt,
                const bool &recursive);
        static bool IsEncrypted(const std::string &path, const std::string &mKey,
                const std::string &mValue);
};

#endif

