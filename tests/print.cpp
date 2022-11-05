#include <string.h>
#include <ncurses.h>

int main(int argc,char* argv[]){
    initscr();//打开ncurses模式
    raw();
    noecho();//关闭回显 让键盘输入的字符不显示在终端上 echo()显示字符
    // curs_set(0);

    const char* ptr = "Hello, StephenWen!";

    mvprintw(LINES/2,(COLS-strlen(ptr))/2,ptr);
    refresh();

    getch();
    endwin();//关闭窗口stdscr

    return 0;
}