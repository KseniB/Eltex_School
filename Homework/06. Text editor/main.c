#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "lib/lib.h"

#define MAX_SIZE 50

WINDOW* btmwnd;
int row = 0, col = 0, line = 0;
int fd, width, height;
char filename[MAX_SIZE];

int main()
{
	initscr();
	signal(SIGWINCH, sig_winch);
	keypad(stdscr, TRUE);

	width = getmaxx(stdscr);
	height = getmaxy(stdscr);

	start();

	while (1)
	{
		move(row, col);
		refresh();
		keypad_func();
	}

	delwin(btmwnd);
	endwin();
    exit(EXIT_SUCCESS);
}
