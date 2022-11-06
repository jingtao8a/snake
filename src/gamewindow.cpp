#include "../include/gamewindow.hpp"
#include <stdlib.h>
#include <time.h>

namespace SNAKE {

GameWindow::GameWindow() {
    srand(time(NULL));//设置随机数种子
    m_gameOver = false;
    initscr();
    noecho();//不回显
    curs_set(0);//隐藏光标
    m_win = stdscr;
    getmaxyx(m_win, m_winHeight, m_winWidth);
    box(m_win, '#', '#');
    initSnake();
    initFood();
}

GameWindow::~GameWindow() {
    getch();
    endwin();
}

void GameWindow::start() {
    m_snake->move();
}

void GameWindow::generateFood() {
    {
        //加读锁
        YXTWebCpp::ReadScopedLockImpl<YXTWebCpp::RWMutex> guard(m_mutex);
        if (m_foods->size() >= 5) {
            return;
        }
    }
    //加写锁
    YXTWebCpp::WriteScopedLockImpl<YXTWebCpp::RWMutex> guard(m_mutex);
    Food food;
    food.generateRandomPositon(m_snake, m_winWidth, m_winHeight);
    m_foods->push_back(food);//新增食物
    //将食物画出来
    wmove(m_win, food.getY(), food.getX());
    wprintw(m_win, "+");
    refresh();
}
void GameWindow::setSnakeDirection(char ch) {
    switch(ch) {
        case 65:
            if (m_snake->getDirection() == Snake::Direction::DOWN) {//不允许掉头
                break;
            }
            m_snake->setDirection(Snake::Direction::UP);
            break;
        case 66:
            if (m_snake->getDirection() == Snake::Direction::UP) {
                break;
            }
            m_snake->setDirection(Snake::Direction::DOWN);
            break;
        case 68:
            if (m_snake->getDirection() == Snake::Direction::RIGHT) {
                break;
            }
            m_snake->setDirection(Snake::Direction::LEFT);
            break;
        case 67:
            if (m_snake->getDirection() == Snake::Direction::LEFT) {
                break;
            }
            m_snake->setDirection(Snake::Direction::RIGHT);
            break;
    }
}

void GameWindow::initSnake() {
    m_snake.reset(new Snake);
    std::shared_ptr<std::list<Snake::Point> > body = m_snake->getBody();

    auto iter = body->begin();
    //打印头部
    wmove(m_win, iter->m_y, iter->m_x);
    wprintw(m_win, "@");
    ++iter;
    //打印尾部
    for (; iter != body->end(); ++iter) {
        wmove(m_win, iter->m_y, iter->m_x);
        wprintw(m_win, "$");
    }
    refresh();
    m_snake->addListener([this](std::shared_ptr<std::list<Snake::Point> > oldBody, std::shared_ptr<std::list<Snake::Point> > newBody) {
        if (this->m_snake->isDead()) {//已经咬到自己了
            this->gameOver();
            return;
        }
        //判断有没有撞墙
        auto iter = newBody->begin();
        if (iter->m_x == 0 || iter->m_y == 0 || iter->m_x == this->m_winWidth - 1 || iter->m_y == this->m_winHeight - 1) {
            this->gameOver();
            this->m_snake->setDead(true);
            return;
        }

        //判断有没有吃到果实
        bool eat = false;
        //查看有没有可以吃的果实
        {
            YXTWebCpp::WriteScopedLockImpl<YXTWebCpp::RWMutex> guard(m_mutex);
            for (auto i = this->m_foods->begin(); i != this->m_foods->end(); ++i) {
                if (i->canEatThisFood(newBody)) {
                    //将食物在屏幕上清除
                    wmove(this->m_win, i->getY(), i->getX());
                    wprintw(this->m_win, " ");
                    refresh();
                    this->m_foods->erase(i);
                    eat = true;
                    break;
                }
            }
        }

        //重新绘制蛇的新身体
        iter = newBody->begin();
        wmove(this->m_win, iter->m_y, iter->m_x);
        wprintw(this->m_win, "@");

        iter = oldBody->begin();
        wmove(this->m_win, iter->m_y, iter->m_x);
        wprintw(this->m_win, "$");
        refresh();

        iter = oldBody->end();
        --iter;
        if (!eat) {    
            wmove(this->m_win, iter->m_y, iter->m_x);
            wprintw(this->m_win, " ");
            refresh();
        } else {
            newBody->splice(newBody->end(), *oldBody, iter);//新增一个身体节点
        }
    });
}

void GameWindow::initFood() {
    m_foods.reset(new std::list<Food>);
}

void GameWindow::gameOver() {
    //清屏
    clear();
    //打印game over
    wmove(m_win, m_winHeight / 2, m_winWidth / 5 * 2);
    wprintw(m_win, "game over");
    refresh();
    m_gameOver = true;
}

}