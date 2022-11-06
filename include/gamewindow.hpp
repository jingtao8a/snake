#ifndef _GAMEWINDOW_HPP_
#define _GAMEWINDOW_HPP_

#include <ncurses.h>
#include <atomic>
#include <yxtwebcpp/thread.hpp>
#include "../include/food.hpp"
#include "../include/snake.hpp"
namespace SNAKE {

class GameWindow {
public:
    GameWindow();
    ~GameWindow();
    void start();
    void setSnakeDirection(char ch);
    void generateFood();
    bool isGameOver() { return m_gameOver; }

private:
    void initSnake();
    void initFood();
    void gameOver();

private:
    uint16_t m_winHeight;
    uint16_t m_winWidth;
    WINDOW *m_win;
    std::shared_ptr<Snake> m_snake;
    std::shared_ptr<std::list<Food> > m_foods;
    std::atomic<bool> m_gameOver;
    YXTWebCpp::RWMutex m_mutex;
};

}

#endif