#include <ncurses.h>

static uint16_t winHeightNumber;
static uint16_t winWidthNumber;

int main() {
    initscr();
    getmaxyx(stdscr, winHeightNumber, winWidthNumber);
    box(stdscr, '.', '.');
    wmove(stdscr, winHeightNumber / 5, 1);
    char ch = 'a';
    for (int i = 2; i <= winWidthNumber - 1; ++i) {
        wprintw(stdscr, "%c", ch);
        ch++;
        if (ch > 'z') {
            ch = 'a';
        }
    }
    

    getch();
    endwin();
    return 0;
}