#include "lib.h"

char open_file(char *file_name, struct winsize size)
{
	int file;
	file = open(file_name, O_CREAT, O_RDWR);
	char buff[81];
	
	if (file == -1)
	{
		printw("File wrong");
	}
	else
	{
		move(0, 0);
		for (int i = 0; i < size.ws_row - 2; i++)
		{
			memset(buff, 0 , 81);
			read(file, buff, 80);
			move(i, 0);
			printw("%s", buff);
		}
		move(size.ws_row - 1, 0);
		printw("File '%s' is opened! Press 'esc' to exit", file_name);
	}
	close(file);
}

void draw_input(char *file_name, struct winsize size)
{
    move(size.ws_row - 1, 0);
    printw("Input file name: ");	
    refresh();
    nocbreak();
    echo();
    wgetnstr(stdscr, file_name, 30);
    move(size.ws_row - 1, 0);
    printw("                                                  \0");
    move(size.ws_row - 1, 0);
}

int start_draw(struct winsize size)
{
    int t;
    cbreak;
    curs_set(FALSE);
    move(size.ws_row - 1, 0);
    printw("Open file - F1 | Save file - F2 | Exit - F3");
    move(size.ws_row - 1, 0);
    t = getch();
    printw("                                                                                                                   \0");	
    refresh();	
    return t;
}
