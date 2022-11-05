#include "../include/gamewindow.hpp"

namespace SNAKE {

GameWindow::GameWindow() {
    initscr();
    m_win = stdscr;
    getmaxyx(m_win, m_winHeight, m_winWidth);
    box(m_win, '#', '#');
}



}