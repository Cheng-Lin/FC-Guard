#include "security/EncryptionMethod.hpp"
#include "security/RandomEncryptionMethod.hpp"
#include "util/FileTools.hpp"
#include "util/InterfaceTools.hpp"

#include <atomic>
#include <boost/program_options.hpp>
#include <curses.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
namespace po = boost::program_options;

atomic<int> counter(-1);

void processDecryption(const EncryptionMethod *decryptor, const vector<string> &file_list,
        const bool &force, const bool &deletefile)
{
    int i = ++counter;
    while (i < file_list.size())
    {
        decryptor->decrypt(file_list[i], force, deletefile);
        cout << "Decrypting [" << file_list[i] << "] Completed" << endl;
        i = ++counter;
    }
}

int main(int argc, const char* argv[])
{
    po::variables_map vm = InterfaceTools::ParseArguementsDecryptor(argc, argv);
    string filename = vm[InterfaceTools::INPUT].as<string>();
    bool force = vm.count(InterfaceTools::FORCE);
    bool deletefile = vm.count(InterfaceTools::DELETE_FILE);
    bool recursive = vm.count(InterfaceTools::RECURSIVE);
    int numThreads = vm[InterfaceTools::THREADS].as<int>();

    vector<string> file_list = FileTools::GetFileList(filename,
            RandomEncryptionMethod::METADATA_KEY,
            RandomEncryptionMethod::METADATA_VALUE_ENCRYPT,
            true, recursive);

    string password = InterfaceTools::GetPassword("Please enter a password: ");

    EncryptionMethod* decryptor = new RandomEncryptionMethod(password);
    vector<thread> threads;
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(thread(processDecryption, ref(decryptor), ref(file_list), ref(force),
                ref(deletefile)));
    }

    for (thread &t : threads) {
        t.join();
    }

    delete decryptor;
    return 0;
}

