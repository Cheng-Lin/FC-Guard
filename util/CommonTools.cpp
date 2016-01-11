#include "CommonTools.hpp"

bool CommonTools::IsLittleEndian()
{
    int num = 1;
    return *(char *)&num == 1;
}

