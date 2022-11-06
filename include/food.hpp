#ifndef _FOOD_HPP_
#define _FOOD_HPP_
#include <stdint.h>
#include "snake.hpp"
namespace SNAKE {

class Food {
public:
    Food();
    bool canEatThisFood(std::shared_ptr<std::list<Snake::Point> > newBody);
    void generateRandomPositon(std::shared_ptr<Snake> snake, uint16_t widthLimit, uint16_t heightLimit);

    uint16_t getX() { return m_x; }
    uint16_t getY() { return m_y; }

private:
    uint16_t m_x;
    uint16_t m_y;
};

}


#endif