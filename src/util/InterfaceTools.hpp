#ifndef INTERFACE_TOOLS_HPP__
#define INTERFACE_TOOLS_HPP__

#include <boost/program_options.hpp>
#include <string>

class InterfaceTools
{
    public:
        static bool GetConfirmation(const std::string &prompt);
        static std::string GetPassword(const char *prompt);
        static boost::program_options::variables_map ParseArguementsEncryptor(int argc,
                const char* argv[]);
        static boost::program_options::variables_map ParseArguementsDecryptor(int argc,
                const char* argv[]);

        static const std::string DELETE_FILE;
        static const std::string HELP;
        static const std::string FORCE;
        static const std::string INPUT;
        static const std::string RECURSIVE;
        static const std::string RE_ENCRYPT;
        static const std::string THREADS;

    private:
        static void AddCommonArguements(
                boost::program_options::options_description &description);
        static boost::program_options::variables_map ParseCommonArguements(
                int argc,
                const char* argv[],
                const boost::program_options::options_description &description);

        static const char* DELETE_FILE_CMD;
        static const char* HELP_CMD;
        static const char* FORCE_CMD;
        static const char* INPUT_CMD;
        static const char* RECURSIVE_CMD;
        static const char* RE_ENCRYPT_CMD;
        static const char* THREADS_CMD;

        static const char* DELETE_FILE_INFO;
        static const char* HELP_INFO;
        static const char* FORCE_INFO;
        static const char* INPUT_INFO;
        static const char* RECURSIVE_INFO;
        static const char* RE_ENCRYPT_INFO;
        static const char* THREADS_INFO;
};

#endif
