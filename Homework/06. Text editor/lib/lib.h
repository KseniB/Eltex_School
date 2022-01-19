#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <termios.h> 
#include <sys/ioctl.h> 
#include <signal.h> 
#include <stdlib.h> 
#include <curses.h> 

struct winsize size;

char open_file(char *file_name, struct winsize size);
void draw_input(char *file_name, struct winsize size);
int start_draw(struct winsize size);
