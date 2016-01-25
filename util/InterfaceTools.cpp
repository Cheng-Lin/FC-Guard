#include "InterfaceTools.hpp"

#include <curses.h>
#include <string>

using namespace std;

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
