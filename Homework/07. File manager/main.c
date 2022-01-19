#include "lib/lib.h"

void sig_winch(int signo)
{
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}

int main()
{
    /*Структура хранит имена файлов в директории для левого окна*/
	struct dirent **buff_l;
	/*Структура хранит имена файлов в директории для правого окна*/
	struct dirent **buff_r;
	/*Структура для понимания типа файла*/
	struct stat sb; 
	
	pid_t pid;
	pthread_t tid;
	
	/*Переменные для хранения количества файлов в директории*/
	int l, r;
	/*Символ для отслеживания нажатий*/
	int symb; 
	/*Положение курсора на экране (y = 0 левое окно, y = 1 правое окно)*/
	int x, y;
	/*Отвечает за количество символов в пути*/
	int len;
	
	long long wr_file;
	int copy = 0;
	int file1, file2;
	int chek;
	
	/*Путь до директории левого окна*/
	char *path_l; 
	/*Путь до директории правого окна*/
	char path_r[255]; 
	
	char copy_path[255];
	char copy_buff;
	
	path_l = getenv("PWD");
	strcpy(path_r, path_l);
	l = scandir(path_l, &buff_l, NULL, alphasort);
	r = scandir(path_r, &buff_r, NULL, alphasort);
	
	initscr();
	keypad(stdscr, true);
	keypad(wnd_r, true);
	keypad(wnd_l, true);
	signal(SIGWINCH, sig_winch);
	
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    init_pair(3, COLOR_RED, COLOR_BLUE);
    
	x = 1;
	y = 0;
	
	while(1)
	{
		curs_set(FALSE);
		cbreak();
		noecho();
		ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
		boxes(size, path_l, path_r);
		print_dirs(buff_l, l, buff_r, r, x, y);
		symb = getch();
		switch(symb)
		{
			case KEY_UP:
				if(x > 1)
					x--;
			break;
				
			case KEY_DOWN:
				if(y == 0 && x < l - 1)
					x++;
				if(y == 1 && x < r - 1)
					x++;
			break;
			
			case KEY_BTAB:
				if(y == 0) 	y++;
				else 		y  = 0;
				x = 1;
			break;
			
			case 10:
				if(y == 0)
				{
					len = strlen(path_l);
					chek = strcmp(buff_l[x]->d_name, "..");
					
					if(chek == 0)
					{
						for(int i = len; i >= 0; i--)
						{ 
							if(path_l[i] == '/')
							{
								path_l[i] = '\0';
								break;
							}
						}
					}
					else
					{
						strncat(path_l,  "/", 1);
		                strncat(path_l, buff_l[x]->d_name,  50);		
					}
					/*Если надо будет понять что за файл мы пытаемся открыть*/
					if (lstat(path_l, &sb) == -1)
					{
                        perror("lstat");
                        exit(EXIT_FAILURE);
                    }
           			
                    file_size = sb.st_size;
					l = scandir(path_l, &buff_l, NULL, alphasort); 
					if(l == -1)
					{
						if(copy == 1)
						{
							pthread_create(&tid, NULL, dr_copy, &wr_file);
							file1 = open(path_l, O_RDONLY);
							strncat(copy_path, path_r,  100);
							strncat(copy_path, "/", 1);
							strncat(copy_path, buff_l[x]->d_name, 100);
							close(creat(copy_path, 0664));
							file2 = open(copy_path, O_RDWR | O_CREAT | O_TRUNC);
							
							while(read(file1, &copy_buff, sizeof(copy_buff)) > 0)
							{ 
								write(file2, &copy_buff, sizeof(copy_buff));
								wr_file++;
								/*Замедление процесса копирования для отображения результата*/
								usleep(1000);
							}
							
							pthread_join(tid, NULL);
							close(file1);
							close(file2);
							memset(copy_path, 0, sizeof(copy_path));
						
							copy = 0;
							wr_file =  0;
							init_pair(1, COLOR_BLUE, COLOR_GREEN);
							init_pair(2, COLOR_YELLOW, COLOR_BLUE); 
							len = strlen(path_l);
							for(int i = len; i >= 0; i--)
							{
                                if(path_l[i] == '/')
                                {
                                   	path_l[i] = '\0';
                                    break;
                                }
                            }
		                    
							l = scandir(path_l, &buff_l, NULL, alphasort);
							r = scandir(path_r, &buff_r, NULL, alphasort);
					    } 
					    else 
					    {
							pid = fork();
							if(pid == 0)
							{
								delwin(wnd_l);
								delwin(wnd_r);
								endwin();
								system("clear");
								execl(path_l, NULL);
							}
							else
							{
                                wait(NULL);
                                initscr();
                                signal(SIGWINCH, sig_winch);
                                start_color();
                                curs_set(FALSE);
                                boxes(size, path_l, path_r);
                                print_dirs(buff_l, l, buff_r, r, x, y);
                                keypad(stdscr, true);
                                keypad(wnd_r, true);
                                keypad(wnd_l, true);
                                refresh();
                                wrefresh(wnd_l);
                                wrefresh(wnd_r);
								
								len = strlen(path_l);
								for(int i = len; i >= 0; i--)
								{
                                    if(path_l[i] == '/')
                                    {
                                        path_l[i] = '\0';
                                        break;
                                    }
                                }
								l = scandir(path_l, &buff_l, NULL, alphasort);
							}
                        }
					}
				}
				else
				{
                    len = strlen(path_r);
                    chek = strcmp(buff_r[x]->d_name, "..");
                    if(chek == 0)
                    {
                        for(int i = len; i >= 0; i--)
                        {
                            if(path_r[i] == '/')
                            {
                                path_r[i] = '\0';
                                break;
                            }
                        }
                    }
                    else
                    {
                        strncat(path_r,  "/", 1);
                        strncat(path_r, buff_r[x]->d_name,  50);
                    }
                    
                    r = scandir(path_r, &buff_r, NULL, alphasort);
                    if(r == -1)
                    {
						pid = fork();
						if(pid == 0)
						{
							delwin(wnd_r);
							delwin(wnd_l);
							endwin();
							system("clear");
							execl(path_r, NULL);
							getch();
							return 0;
						}
						else
						{
							wait(NULL);
							initscr();
							signal(SIGWINCH, sig_winch);
                            start_color();
                            curs_set(FALSE);
							boxes(size, path_l, path_r);
							print_dirs(buff_l, l, buff_r, r, x, y);
							keypad(stdscr, true);
                            keypad(wnd_r, true);
                            keypad(wnd_l, true);
                            refresh();
							wrefresh(wnd_l);
							wrefresh(wnd_r);
							
							len = strlen(path_r);
							for(int i = len; i >= 0; i--)
							{
                                if(path_r[i] == '/')
                                {
                                    path_r[i] = '\0';
                                    break;
                                }
                            }
							r = scandir(path_r, &buff_r, NULL, alphasort);
						}
					}	
				}
				refresh();
				wrefresh(wnd_l);
				wrefresh(wnd_r);
				
				x = 1;
			break;
			
			case 'c':
				if(copy == 0)
				{
					copy = 1;
					init_pair(2, COLOR_BLUE, COLOR_GREEN);
					init_pair(1, COLOR_YELLOW, COLOR_BLUE);
				}
				else
				{
					copy = 0;
					init_pair(1, COLOR_BLUE, COLOR_GREEN);
					init_pair(2, COLOR_YELLOW, COLOR_BLUE); 
				}
			break;
			
			case  27:
				echo();
				curs_set(TRUE);
				nocbreak;
				free(buff_r);
				free(buff_l);
				delwin(wnd_r);
                delwin(wnd_l);
                endwin();
				system("clear");
				exit(0);
		}

		refresh();
		wrefresh(wnd_l);
		wrefresh(wnd_r);
	}
	
	return 0;
}
