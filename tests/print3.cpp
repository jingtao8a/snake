
#include <ncurses.h>
 
int main()
{
 
	initscr();
	start_color();
	clear();
	noecho();
	cbreak();
 
	int now_x = 10;
	int now_y = 10;
	mvprintw(now_y, now_x, "@$@");
 
	int ch;
	while (1)
	{
		ch = getch();
		mvprintw(0,0,"%d%d%d",ch,now_y,now_x);
		switch (ch)
		{
		case 65:
			--now_y;
			break;
		case 66:
			++now_y;
			break;
		case 68:
			--now_x;
			break;
		case 67:
			++now_x;
			break;
		}
		clear();
		mvprintw(now_y,now_x,"@$@");
		refresh();
	}
		
		
	endwin();
 
	return 0;
}