#include "FileTools.hpp"

#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/xattr.h>
#include <vector>

using namespace std;
namespace fs = boost::filesystem;

vector<string> FileTools::GetFileList(const string &path, const string &mKey, const string &mValue,
        const bool &reencrypt, const bool &recursive)
{
    vector<string> file_list;

    fs::path full_path = fs::absolute(path);
    if (fs::exists(full_path) && !fs::is_directory(full_path))
    {
        if (!reencrypt && FileTools::IsEncrypted(path, mKey, mValue)) {
            cout << "File [" << path << "] already encrypted." << endl;
            exit(1);
        }
        file_list.push_back(full_path.string());
        return file_list;
    }

    boost::system::error_code err;
    if (recursive)
    {
        for (fs::recursive_directory_iterator end, it(full_path, err); it != end;
                it.increment(err))
        {
            if (!err.value() && is_regular_file(*it)) {
                string temp = fs::path(*it).string();
                if (reencrypt || !FileTools::IsEncrypted(temp, mKey, mValue)) {
                    file_list.push_back(temp);
                }
            }
        }
    }
    else
    {
        for (fs::directory_iterator end, it(full_path, err); it != end; it.increment(err))
        {
            if (!err.value() && is_regular_file(*it)) {
                string temp = fs::path(*it).string();
                if (reencrypt || !FileTools::IsEncrypted(temp, mKey, mValue)) {
                    file_list.push_back(temp);
                }
            }
        }
    }

    return file_list;
}

bool FileTools::IsEncrypted(const string &path, const string &mKey, const string &mValue)
{
    char value[mValue.size() + 1];
    if (getxattr(path.c_str(), mKey.c_str(), value, mValue.size() + 1) == -1) {
        return false;
    }
    value[mValue.size()] = '\0';
    if (strcmp(value, mValue.c_str()) == 0) {
        return true;
    }
    return false;
}

