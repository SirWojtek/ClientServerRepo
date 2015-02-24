
#include "KeyGetter.hpp"

#include <ncurses.h>

KeyGetter::KeyGetter()
{
    initscr();
    timeout(-1);
    noecho();
}

KeyGetter::~KeyGetter()
{
    endwin();
}

char KeyGetter::getPressedKey() const
{
    return static_cast<char>(getch());
}




