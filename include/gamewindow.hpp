#ifndef _GAMEWINDOW_HPP_
#define _GAMEWINDOW_HPP_

#include <ncurses.h>

namespace SNAKE {

class GameWindow {
public:
    GameWindow();
    
private:
    uint16_t m_winHeight;
    uint16_t m_winWidth;
    WINDOW *m_win;
};

}

#endif