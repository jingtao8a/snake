#include "../include/snake.hpp"
#include <unistd.h>

namespace SNAKE{

Snake::Snake() {
    m_listeners.reset(new std::map<uint32_t, fun>);
    //snake body init length = 4 head direction = down
    m_body.reset(new std::list<Point>);
    m_body->push_back(Point(2, 3));
    m_body->push_back(Point(2, 2));
    m_body->push_back(Point(2, 1));    
    m_body->push_back(Point(1, 1));
    m_headDirection = Direction::DOWN;
    m_Dead = false;
}

void Snake::move() {
    while (true) {
        std::shared_ptr<std::list<Point> > newBody(new std::list<Point>);
        *newBody = *m_body;
        newBody->pop_back();
        Point head = *(newBody->begin());
        Direction direction = getDirection();
        switch(direction) {
            case Direction::DOWN:
                head.m_y++;
                break;
            case Direction::UP:
                head.m_y--;
                break;
            case Direction::LEFT:
                head.m_x--;
                break;
            case Direction::RIGHT:
                head.m_x++;
                break;
        }
        newBody->push_front(head);
        m_Dead = biteSelf(newBody);
        setBody(newBody);//设置新的身体
        if (m_Dead) {
            break;
        }
        usleep(300000);
    }
}

Snake::Direction Snake::getDirection() {
    YXTWebCpp::ScopedLockImpl<YXTWebCpp::Mutex> guard(m_mutex);
    return m_headDirection;
}

void Snake::setDirection(Direction direction) {
    m_mutex.lock();
    m_headDirection = direction;
    m_mutex.unlock();
}

bool Snake::biteSelf(std::shared_ptr<std::list<Point> > newBody) {
    auto iter = newBody->begin();
    Point head = *iter;
    iter++;
    for (; iter != newBody->end(); ++iter) {
        if (head == *iter) {
            return true;
            break;
        }
    }
    return false;
}


Snake::Point::Point() {}

Snake::Point::Point(uint16_t x, uint16_t y) {
    m_x = x;
    m_y = y;
}

void Snake::setBody(std::shared_ptr<std::list<Point> > newBody) {
    for (auto& i : *m_listeners) {
        i.second(m_body, newBody);
    }
    m_body = newBody;
}

std::shared_ptr<std::list<Snake::Point> > Snake::getBody() {
    std::shared_ptr<std::list<Point> > body(new std::list<Point>);
    *body = *m_body;
    return body;
}

void Snake::addListener(fun cb) {
    static uint32_t listenerID = 0;
    listenerID++;
    m_listeners->insert(std::make_pair(listenerID, cb));
}

}