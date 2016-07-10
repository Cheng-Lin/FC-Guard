#include "InterfaceTools.hpp"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <string>

#define DELETE_FILE_DEF "delete-file"
#define HELP_DEF        "help"
#define FORCE_DEF       "force"
#define INPUT_DEF       "input"
#define RECURSIVE_DEF   "recursive"
#define RE_ENCRYPT_DEF  "re-encrypt"
#define THREADS_DEF     "threads"

using namespace std;
namespace po = boost::program_options;

const string InterfaceTools::DELETE_FILE = DELETE_FILE_DEF;
const string InterfaceTools::HELP = HELP_DEF;
const string InterfaceTools::FORCE = FORCE_DEF;
const string InterfaceTools::INPUT = INPUT_DEF;
const string InterfaceTools::RECURSIVE = RECURSIVE_DEF;
const string InterfaceTools::RE_ENCRYPT = RE_ENCRYPT_DEF;
const string InterfaceTools::THREADS = THREADS_DEF;

const char* InterfaceTools::DELETE_FILE_CMD = DELETE_FILE_DEF ",d";
const char* InterfaceTools::HELP_CMD = HELP_DEF ",h";
const char* InterfaceTools::FORCE_CMD = FORCE_DEF ",f";
const char* InterfaceTools::INPUT_CMD = INPUT_DEF ",i";
const char* InterfaceTools::RECURSIVE_CMD = RECURSIVE_DEF ",r";
const char* InterfaceTools::RE_ENCRYPT_CMD = RE_ENCRYPT_DEF;
const char* InterfaceTools::THREADS_CMD = THREADS_DEF ",t";

const char* InterfaceTools::DELETE_FILE_INFO = "Delete the original file";
const char* InterfaceTools::HELP_INFO = "Help Screen";
const char* InterfaceTools::FORCE_INFO = "Ignore all warnings";
const char* InterfaceTools::INPUT_INFO = "Input can either be a file or directory";
const char* InterfaceTools::RECURSIVE_INFO = "Traverse all the subdirectories "
        "(only works with directory)";
const char* InterfaceTools::RE_ENCRYPT_INFO = "Encrypt the encrypted file again";
const char* InterfaceTools::THREADS_INFO = "Number of threads to use";

bool InterfaceTools::GetConfirmation(const string &prompt)
{
    cout << prompt << " [y/n] ";
    string line;
    getline(cin, line);
	return (line.compare("y") == 0) || (line.compare("Y") == 0);
}

string InterfaceTools::GetPassword(const char *prompt)
{
    initscr();
    printw(prompt);
    noecho();

    char buff[256];
    getnstr(buff, sizeof(buff));

    echo();
    endwin();
    return buff;
}

po::variables_map InterfaceTools::ParseArguementsEncryptor(int argc, const char* argv[])
{
    try
    {
        po::options_description description("Encryption Options");
        InterfaceTools::AddCommonArguements(description);
        description.add_options()
                (InterfaceTools::RE_ENCRYPT_CMD, InterfaceTools::RE_ENCRYPT_INFO);

        return InterfaceTools::ParseCommonArguements(argc, argv, description);
    }
    catch (const po::error &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
}

po::variables_map InterfaceTools::ParseArguementsDecryptor(int argc, const char* argv[])
{
    try
    {
        po::options_description description("Decryption Options");
        InterfaceTools::AddCommonArguements(description);

        return InterfaceTools::ParseCommonArguements(argc, argv, description);
    }
    catch (const po::error &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
}

void InterfaceTools::AddCommonArguements(po::options_description &description)
{
    description.add_options()
            (InterfaceTools::HELP_CMD, InterfaceTools::HELP_INFO)
            (InterfaceTools::FORCE_CMD, InterfaceTools::FORCE_INFO)
            (InterfaceTools::INPUT_CMD, po::value<string>()->required(),
                    InterfaceTools::INPUT_INFO)
            (InterfaceTools::DELETE_FILE_CMD, InterfaceTools::DELETE_FILE_INFO)
            (InterfaceTools::RECURSIVE_CMD, InterfaceTools::RECURSIVE_INFO)
            (InterfaceTools::THREADS_CMD, po::value<int>()->default_value(1),
                    InterfaceTools::THREADS_INFO);
}

po::variables_map InterfaceTools::ParseCommonArguements(int argc, const char* argv[],
        const po::options_description &description)
{
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).run(), vm);

    if (vm.count(InterfaceTools::HELP)) {
        cout << description << endl;
        exit(0);
    }
    po::notify(vm);
    if (vm[InterfaceTools::THREADS].as<int>() < 1) {
        cerr << "Number of threads has to be greater than 0" << endl;
        exit(1);
    }

    return vm;
}

