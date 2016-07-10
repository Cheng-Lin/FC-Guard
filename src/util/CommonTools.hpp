#ifndef COMMON_TOOLS_HPP__
#define COMMON_TOOLS_HPP__

#include <fstream>

class CommonTools
{
    public:
        static std::size_t GetFileSize(std::ifstream &fin);
        static bool IsLittleEndian();
};

#endif

