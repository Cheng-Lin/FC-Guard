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

void processEncryption(const EncryptionMethod *encryptor, const vector<string> &file_list,
        const bool &force, const bool &deletefile)
{
    int i = ++counter;
    while (i < file_list.size())
    {
        encryptor->encrypt(file_list[i], force, deletefile);
        cout << "Encrypting [" << file_list[i] << "] Completed" << endl;
        i = ++counter;
    }
}

int main(int argc, const char* argv[])
{
    po::variables_map vm = InterfaceTools::ParseArguementsEncryptor(argc, argv);
    string filename = vm[InterfaceTools::INPUT].as<string>();
    bool force = vm.count(InterfaceTools::FORCE);
    bool deletefile = vm.count(InterfaceTools::DELETE_FILE);
    bool recursive = vm.count(InterfaceTools::RECURSIVE);
    bool reencrypt = vm.count(InterfaceTools::RE_ENCRYPT);
    int numThreads = vm[InterfaceTools::THREADS].as<int>();

    vector<string> file_list = FileTools::GetFileList(filename,
            RandomEncryptionMethod::METADATA_KEY,
            RandomEncryptionMethod::METADATA_VALUE_ENCRYPT,
            reencrypt, recursive);

    string password;
    bool notSame = false;
    do {
        if (notSame) {
            printw("\nPassword entered does not match, pelase try again.\n");
        }
        password = InterfaceTools::GetPassword("Please enter a password: ");
        notSame = password.compare(InterfaceTools::GetPassword("Please re-enter the password: "))
                != 0;
    } while (notSame);

    EncryptionMethod* encryptor = new RandomEncryptionMethod(password);
    vector<thread> threads;
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(thread(processEncryption, ref(encryptor), ref(file_list), ref(force),
                ref(deletefile)));
    }

    for (thread &t : threads) {
        t.join();
    }

    delete encryptor;
    return 0;
}

