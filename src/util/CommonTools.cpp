#include "CommonTools.hpp"

#include <fstream>

using namespace std;

size_t CommonTools::GetFileSize(ifstream &fin)
{
    streampos loc = fin.tellg();
    fin.seekg(0, fin.end);
    size_t size = fin.tellg();
    fin.seekg(loc);
    return size;
}

bool CommonTools::IsLittleEndian()
{
    int num = 1;
    return *(char *)&num == 1;
}

