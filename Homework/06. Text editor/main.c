#include "lib/lib.h"

int main()
{
	int file = 0;
	char file_name[30];
	chtype *str;
	int symb;
	int chek;
	bool ex =  false;
 	str = calloc(80, sizeof(chtype));
 	
	initscr();
  	keypad(stdscr, true);
  	
	while (1)
	{
  		signal(SIGWINCH, sig_winch);	
		curs_set(FALSE);
		start_color();
		cbreak();
		refresh();
		noecho();
		ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
		
		switch (start_draw(size))
		{
			case KEY_F(1):	
				ex = false;
				curs_set(TRUE);
				start_color();
				draw_input(file_name, size);
				open_file(file_name, size);
				
				int x = 0;
				int y = 0;
				move(x, y);
				cbreak();
				noecho();
				keypad(stdscr, true);
				refresh();
				do
				{
					symb = getch();
					switch (symb)
					{
						case KEY_UP:
							if (x > 0)
							{
								x--;
							}
							move(x, y);
						break;
						
						case KEY_DOWN:
							if (x < (size.ws_row - 1))
							{
								x++;
							}
							move(x, y);	
						break;
						
						case KEY_LEFT:
							if (y > 0)
							{
								y--;
							}
							move(x, y);
						break;
						
						case KEY_RIGHT:
							if (y < (size.ws_col - 1))
							{
								y++;
							}
							move(x, y);
						break;
						
						case 27:
							ex = true;
						break;
						
						case KEY_BACKSPACE:
							if (y == 0)
							{
								move(size.ws_row - 1, 0);
								printw("                                                                     \0");
								move(size.ws_row - 1 , size.ws_col/2);
								printw("                             \0");
								move(x, y);
								deleteln();
								x--;
								move(size.ws_row - 1, 0);
								printw("File '%s' is opened! Press 'esc' to exit", file_name);
								move(x, 80);
							}
							else
							{
								y--;
								move(x, y);
								delch();
							}
							move(x, y);
						break;
						
						case 10:
							move(size.ws_row - 1, 0);
							printw("                                                                  \0");
							x++;
							move(x, 0);
							insdelln(1);
							move(size.ws_row - 1, 0);
							printw("File '%s' is opened! Press 'esc' to exit", file_name);
							move(x, y);
						break;
						
						default :
							insch(symb);
							y++;
							move(x, y);
						break;
					}
					
					move(size.ws_row - 1 , size.ws_col/2);
					printw("                             \0");
					move(size.ws_row - 1 , size.ws_col/2);
					printw("(%d, %d)", x, y);
					move(x, y);
					refresh();
				} while (!ex);			
			break;
			
			case KEY_F(2):
				x = 0;
				y = 0;
				move(size.ws_row - 1, 0);
				printw("                                                  \0");
				file = open(file_name, O_WRONLY);
				
				if (file == -1)
				{
					printf("File wrong");
				}
				else
				{
					for (int s = 0; s < size.ws_row - 2; s++)
					{
						mvinchnstr(s, 0, str, 79);
						for (int i = 0; i < 80; i++)
						{
							chek = write(file, &str[i], 1);
							if (chek == -1)
							{
								move(10,10);
								printf("Error of input to file");
								getch();
							}
						}
					}
					close(file);
				}
				
				move(size.ws_row - 1, 0);
				printw("file %s saved", file_name);
				getch();
				
				for (int i = 0; i < size.ws_row - 2; i++)
				{
					move(i, 0);
					printw("                                                                                               \0");
				}
				refresh();
			break;
			
			case KEY_F(3):
				endwin();
				free(str);
				exit(0);
			break;
				
			default:
				printw("Input error");	
			break;
		}
	}
	
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	
	return 0;
}
