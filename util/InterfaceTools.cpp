#include "InterfaceTools.hpp"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <string>

using namespace std;
namespace po = boost::program_options;

const string InterfaceTools::DELETE_FILE = "delete-file";
const string InterfaceTools::HELP = "help";
const string InterfaceTools::FORCE = "force";
const string InterfaceTools::INPUT = "input";
const string InterfaceTools::RECURSIVE = "recursive";
const string InterfaceTools::RE_ENCRYPT = "re-encrypt";
const string InterfaceTools::THREADS = "threads";

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

po::variables_map InterfaceTools::ParseArguement(int argc, const char* argv[])
{
    try
    {
        po::options_description description("Encyption/Decryption Options");
        description.add_options()
                ((InterfaceTools::HELP + ",h").c_str(), "Help Screen")
                ((InterfaceTools::FORCE + ",f").c_str(), "Ignore all warnings")
                ((InterfaceTools::INPUT + ",i").c_str(), po::value<string>()->required(),
                        "Input can either be a file or directory")
                ((InterfaceTools::DELETE_FILE + ",d").c_str(), "Keep original file")
                ((InterfaceTools::RECURSIVE + ",r").c_str(), "Only works with directory, "
                        "all subdirectories will be traversed")
                (InterfaceTools::RE_ENCRYPT.c_str(), "Encrypt the encrypted file again")
                ((InterfaceTools::THREADS + ",t").c_str(), po::value<int>()->default_value(1),
                        "Number of threads to use");

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
    catch (const po::error &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
}

