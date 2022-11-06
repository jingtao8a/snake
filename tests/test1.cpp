#include "../include/gamewindow.hpp"
#include <yxtwebcpp/thread.hpp>
#include <vector>

std::shared_ptr<SNAKE::GameWindow> gameWindow(new SNAKE::GameWindow);

int main() {
    std::shared_ptr<YXTWebCpp::Thread> thread1(new YXTWebCpp::Thread([](){        
        gameWindow->start();
    }, "greedy snake"));
    
    std::shared_ptr<YXTWebCpp::Thread> thread2(new YXTWebCpp::Thread([](){
        while (!gameWindow->isGameOver()) {//游戏还未结束，则读取键盘的按键
            char ch = getch();
            gameWindow->setSnakeDirection(ch);
        }
    }, "deal with keyboard"));
    std::shared_ptr<YXTWebCpp::Thread> thread3(new YXTWebCpp::Thread([](){
        while (!gameWindow->isGameOver()) {
            gameWindow->generateFood();
        }
    }, "generate food"));
    thread1->join();
    thread2->join();
    thread3->join();
    return 0;
}
