#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>  
#include <fcntl.h>           
#include <sys/stat.h>
#include <pthread.h>

/*libs for ncurses work*/
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

struct winsize size;

void print_dirs(struct dirent **buff_l, int l,struct dirent **buff_r, int r, int x, int y);
void boxes(struct winsize size, char *path_l, char *path_r);
void *dr_copy(void *param);

WINDOW* wnd_l;
WINDOW* wnd_r;
WINDOW* wnd_c;

long long file_size;
