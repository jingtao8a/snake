#include <ncurses.h>
#include <stdio.h>
int main()
{
    int winHeightNumber;//窗口高行数
    int winWidthNumber;//窗口宽列数

    WINDOW* upWin = NULL;     //上窗口
    WINDOW* leftWin = NULL;
    WINDOW* rightWin = NULL;

    initscr(); //初始化ncurses


    getmaxyx(stdscr, winHeightNumber, winWidthNumber); //获取stdscr标准窗口的行数 和行宽占字符列数

    if (upWin == NULL)
        upWin = subwin(stdscr, winHeightNumber / 5, winWidthNumber, 0, 0);  //创建子窗口  
    if (leftWin == NULL)
        leftWin = subwin(stdscr, winHeightNumber - winHeightNumber / 5, winWidthNumber / 5 * 4, winHeightNumber / 5, 0);
    if (rightWin == NULL)
        rightWin = subwin(stdscr, winHeightNumber - winHeightNumber / 5, winWidthNumber - winWidthNumber / 5 * 4, winHeightNumber / 5, winWidthNumber / 5 * 4);

    box(upWin, '.', '.');  //画框
    box(leftWin, '.', '.');
    box(rightWin, '.', '.');

    wmove(upWin, 1, 1);   //移动光标
    wprintw(upWin, "%s", "this is upWin");  //窗口打印
    
    wmove(leftWin, 1, 1);
    wprintw(leftWin, "%s", "this is leftWin");

    wmove(rightWin, 1, 1);
    wprintw(rightWin, "%s", "this is rightWin");


    getch();   //等待键盘输入     这是为了让程序停在这里  不让关闭和释放窗口

    delwin(upWin);  //释放窗口
    delwin(leftWin);
    delwin(rightWin);
    endwin();  //关闭stdscr

    return 0;
}