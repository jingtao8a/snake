#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <list>
#include <stdint.h>
#include <memory>
#include <functional>
#include <map>
#include <yxtwebcpp/thread.hpp>

namespace SNAKE {

class Snake {
public:
    struct Point {
        uint16_t m_y;
        uint16_t m_x;
        
        Point();
        Point(uint16_t x, uint16_t y);

        bool operator==(const Point& rhs) {
            return m_x == rhs.m_x && m_y == rhs.m_y;
        }
    };

    enum Direction {
        UP = 100,
        LEFT,
        RIGHT,
        DOWN,
    };
    typedef std::function<void (std::shared_ptr<std::list<Point> > oldBody, std::shared_ptr<std::list<Point> > newBody)> fun;

    Snake();
    
    void move();
    void addListener(fun cb);
    
    void setBody(std::shared_ptr<std::list<Point> > newBody);
    std::shared_ptr<std::list<Point> > getBody();

    bool isDead() { return m_Dead; }
    void setDead(bool flag) { m_Dead = flag; }

    void setDirection(Direction direction);
    Direction getDirection();
private:
    bool biteSelf(std::shared_ptr<std::list<Point> > newBody);

private:
    std::shared_ptr<std::list<Point> > m_body;
    Direction m_headDirection;
    std::shared_ptr<std::map<uint32_t, fun>> m_listeners;
    bool m_Dead;
    YXTWebCpp::Mutex m_mutex;
};

}

#endif