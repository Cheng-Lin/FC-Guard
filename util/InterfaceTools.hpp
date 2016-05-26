#ifndef INTERFACE_TOOLS_HPP__
#define INTERFACE_TOOLS_HPP__

#include <boost/program_options.hpp>
#include <string>

class InterfaceTools
{
    public:
        static bool GetConfirmation(const std::string &prompt);
        static std::string GetPassword(const char *prompt);
        static boost::program_options::variables_map ParseArguement(int argc, const char* argv[]);

        static const std::string DELETE_FILE;
        static const std::string HELP;
        static const std::string FORCE;
        static const std::string INPUT;
        static const std::string RECURSIVE;
        static const std::string RE_ENCRYPT;
};

#endif
