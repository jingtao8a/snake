#include "../include/food.hpp"
#include <stdlib.h>

namespace SNAKE{

Food::Food() {}

bool Food::canEatThisFood(std::shared_ptr<std::list<Snake::Point> > newBody) {
    auto iter = newBody->begin();
    if (iter->m_x == m_x && iter->m_y == m_y) {
        return true;
    }
    return false;
}

void Food::generateRandomPositon(std::shared_ptr<Snake> snake, uint16_t widthLimit, uint16_t heightLimit) {
    while (true) {
        m_x = rand() % widthLimit;
        if (m_x == 0) {
            m_x++;
        }
        if (m_x == widthLimit - 1) {
            m_x--;
        }
        m_y = rand() % heightLimit;
        if (m_y == 0) {
            m_y++;
        }
        if (m_y == heightLimit - 1) {
            m_y--;
        }
        auto body = snake->getBody();
        bool flag = true;
        for (auto& i : *body) {
            if (i.m_x == m_x && i.m_y == m_y) {
                flag = false;
            }
        }
        if (flag) {
            break;
        }
    }
}

}